package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"io/fs"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"text/template"

	"github.com/google/shlex"
)

var (
	dryRun   = flag.Bool("dry-run", false, "don't build, just print makefile")
	o3       = flag.Bool("o3", false, "whether to optimize build")
	outdir   = flag.String("outdir", "build/", "where to place build artifacts")
	parallel = flag.Bool("j", false, "whether to build with -j")
)

type Target interface {
	Name() string
	Dir() string
	Sources() []string
	Deps() []string
}

type Platform interface {
	AssemblyFile(source string) string
	DependenciesFile(source string) string
	ObjectFile(source string) string
	Library(name string) string

	CompileFlags(source string, target Target) string
	AssembleFlags(source string, target Target) string
	DependenciesFlags(source string) string
	LinkFlags(app *App) string

	Binary(app *App) string

	Compiler(source string) string
	Linker() string
}

type STM32L struct{}

func (STM32L) AssemblyFile(source string) string {
	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".stm32l.s")
}

func (STM32L) DependenciesFile(source string) string {
	if filepath.Ext(source) == ".s" {
		return ""
	}

	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".stm32l.d")
}

func (STM32L) ObjectFile(source string) string {
	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".stm32l.o")
}

func (STM32L) Library(name string) string {
	return filepath.Join(*outdir, fmt.Sprintf("lib%s.stm32l.a", name))
}

func (STM32L) CFlags() []string {
	return append([]string{
		"-target",
		"armv6m-none-eabi",
		"-mthumb",
		"-g",
		"-Werror",
		"-nostdlib",
		"-nodefaultlibs",
		"-Wno-unused-command-line-argument",
	}, defaultCFlags()...)
}

func (l STM32L) CCFlags() []string {
	flags := append(l.CFlags(), defaultCFlags()...)
	return append(flags, "--std=c++20")
}

func (l STM32L) CompileFlags(source string, target Target) string {
	var flags []string

	switch filepath.Ext(source) {
	case ".c":
		flags = l.CFlags()
	case ".cc":
		flags = l.CCFlags()
	case ".cpp":
		flags = l.CCFlags()
	case ".s":
		flags = l.CFlags()
	default:
		panic("unsupported source " + source)
	}

	for _, dep := range target.Deps() {
		flags = append(flags, "-I", dep)
	}

	flags = append(flags, "-I", target.Dir())
	flags = append(flags, "-c", source, "-o", l.ObjectFile(source))

	return strings.Join(flags, " ")
}

func (l STM32L) AssembleFlags(source string, target Target) string {
	var flags []string

	switch filepath.Ext(source) {
	case ".c":
		flags = l.CFlags()
	case ".cc":
		flags = l.CCFlags()
	case ".cpp":
		flags = l.CCFlags()
	case ".s":
		flags = l.CFlags()
	default:
		panic("unsupported source " + source)
	}

	for _, dep := range target.Deps() {
		flags = append(flags, "-I", dep)
	}

	flags = append(flags, "-I", target.Dir())
	flags = append(flags, "-S", source, "-o", l.AssemblyFile(source))

	return strings.Join(flags, " ")
}

func (l STM32L) DependenciesFlags(source string) string {
	if filepath.Ext(source) == ".s" {
		return ""
	}

	return strings.Join(
		[]string{
			"-MT",
			l.ObjectFile(source),
			"-MMD",
			"-MP",
			"-MF",
			l.DependenciesFile(source),
		},
		" ",
	)
}

func (l STM32L) LinkFlags(app *App) string {
	return strings.Join(
		[]string{
			"-nostdlib",
			"-nodefaultlibs",
			"-target armv6m-none-eabi",
			"-fno-exceptions",
			"-fno-rtti",
			"-o",
			l.Binary(app),
		},
		" ")
}

func (l STM32L) Binary(app *App) string {
	return filepath.Join(*outdir, fmt.Sprintf("%s.stm32l.exe", app.name))
}

func (l STM32L) Compiler(source string) string {
	return map[string]string{
		".c":   "clang",
		".cc":  "clang++",
		".cpp": "clang++",
		".s":   "clang",
	}[filepath.Ext(source)]
}

func (l STM32L) Linker() string {
	return "clang"
}

type CompileCommand struct {
	Directory string   `json:"directory"`
	Arguments []string `json:"arguments"`
	File      string   `json:"file"`
}

type App struct {
	dir     string
	name    string
	sources []string
	deps    []string
}

func (l *App) Name() string {
	return l.name
}

func (l *App) Dir() string {
	return l.dir
}

func (l *App) Sources() []string {
	return l.sources
}

func (l *App) Deps() []string {
	return l.deps
}

type Lib struct {
	dir     string
	name    string
	sources []string
	deps    []string
}

func (l *Lib) Name() string {
	return l.name
}

func (l *Lib) Dir() string {
	return l.dir
}

func (l *Lib) Sources() []string {
	return l.sources
}

func (l *Lib) Deps() []string {
	return l.deps
}

type Source struct {
	P Platform
	S string
	T Target
}

func main() {
	flag.Parse()

	wd, err := os.Getwd()
	if err != nil {
		panic(err)
	}

	lib := &Lib{
		name:    "lib",
		dir:     "lib",
		sources: findSources("lib"),
	}

	libs := []*Lib{lib}

	apps, err := findApps("apps")
	if err != nil {
		panic(err)
	}

	for _, app := range apps {
		app.deps = append(app.deps, "lib")
	}

	writeCompileCommands(STM32L{}, wd, libs, apps)

	makeArgs := []string{
		"-f",
		"-",
	}

	if *parallel {
		makeArgs = append(makeArgs, "-j")
	}

	args := append(makeArgs, flag.Args()...)

	if !*dryRun {
		cmd := exec.Command("make", args...)
		cmd.Stderr = os.Stderr
		cmd.Stdout = os.Stdout

		stdin, err := cmd.StdinPipe()
		if err != nil {
			panic(err)
		}

		go func() {
			defer stdin.Close()

			data := map[string]any{
				"Apps":   apps,
				"Libs":   libs,
				"Outdir": *outdir,
				"P":      STM32L{},
			}
			if err := makefileTemplate.Execute(stdin, data); err != nil {
				panic(err)
			}
		}()

		if err := cmd.Run(); err != nil {
			if exit, ok := err.(*exec.ExitError); ok {
				fmt.Fprintf(os.Stderr, "exit code: %d\n", exit.ExitCode())
			}
		}
	} else {
		fmt.Printf("DRY RUN: make %v\n", args)

		data := map[string]any{
			"Apps":   apps,
			"Libs":   libs,
			"Outdir": *outdir,
			"P":      STM32L{},
		}
		if err := makefileTemplate.Execute(os.Stdout, data); err != nil {
			panic(err)
		}
	}
}

func writeCompileCommands(p Platform, wd string, libs []*Lib, apps []*App) {
	var commands []CompileCommand

	for _, lib := range libs {
		commands = append(commands, compileCommands(p, wd, lib)...)
	}

	for _, app := range apps {
		commands = append(commands, compileCommands(p, wd, app)...)
	}

	outf, err := os.Create("compile_commands.json")
	if err != nil {
		panic(err)
	}
	defer outf.Close()

	if err := json.NewEncoder(outf).Encode(commands); err != nil {
		panic(err)
	}
}

func compileCommands(p Platform, wd string, target Target) []CompileCommand {
	var commands []CompileCommand

	for _, source := range target.Sources() {
		object := p.ObjectFile(source)

		args := []string{
			p.Compiler(source),
			"-c",
			source,
			"-o",
			object,
		}

		flags, err := shlex.Split(p.CompileFlags(source, target))
		if err != nil {
			panic(err)
		}

		args = append(args, flags...)

		commands = append(commands, CompileCommand{
			Directory: wd,
			Arguments: args,
			File:      source,
		})
	}

	return commands
}

func findApps(dirs ...string) ([]*App, error) {
	var apps []*App
	for _, dir := range dirs {
		entries, err := os.ReadDir(dir)
		if err != nil {
			return nil, err
		}

		for _, entry := range entries {
			appDir := filepath.Join(dir, entry.Name())
			sources := findSources(appDir)

			apps = append(apps, &App{
				dir:     appDir,
				name:    entry.Name(),
				sources: sources,
			})
		}
	}

	return apps, nil
}

func findSources(dirs ...string) []string {
	var sources []string
	for _, dir := range dirs {
		if err := filepath.WalkDir(dir, func(path string, d fs.DirEntry, err error) error {
			// root doesn't exist.
			if d == nil {
				return nil
			}

			if d.IsDir() {
				if strings.HasPrefix(d.Name(), ".") {
					return fs.SkipDir
				}
				return nil
			}

			if sourceExtensions[filepath.Ext(d.Name())] {
				sources = append(sources, path)
			}

			return nil
		}); err != nil {
			panic(err)
		}
	}

	return sources
}

func defaultCFlags() []string {
	var ret []string

	if *o3 {
		ret = append(ret, "-O3")
	}

	return ret
}

var sourceExtensions = map[string]bool{
	".c":   true,
	".cc":  true,
	".cpp": true,
	".s":   true,
}

var makefileTemplate = template.Must(template.New("makefile").Funcs(template.FuncMap{
	"source": func(platform Platform, source string, target Target) Source {
		return Source{platform, source, target}
	},
}).Parse(`
{{define "compile"}}
{{if $.P.DependenciesFile $.S}}
{{$.P.DependenciesFile $.S}}:
{{end}}

{{$.P.ObjectFile $.S}}: {{$.S}}
{{$.P.ObjectFile $.S}}: {{$.S}} {{$.P.DependenciesFile $.S}}
	mkdir -p $(OUTDIR)
	{{$.P.Compiler $.S}} {{$.P.CompileFlags $.S $.T}} {{$.P.DependenciesFlags $.S}}
	{{$.P.Compiler $.S}} {{$.P.AssembleFlags $.S $.T}}
{{end}}
OUTDIR={{$.Outdir}}
	
all: {{range .Apps}} {{$.P.Binary .}} {{end}}
.PHONY: all

{{range $l := .Libs}}
{{range .Sources}}
{{template "compile" source $.P . $l}}
{{end}}

{{$.P.Library .Name}}: {{range .Sources}} {{$.P.ObjectFile .}} {{end}}
	rm -rf {{$.P.Library .Name}}; ar rcs {{$.P.Library .Name}} $^
	
{{end}}

{{range $a := .Apps}}
{{range .Sources}}
{{template "compile" source $.P . $a}}
{{end}}
{{end}}

clean:
	rm -rf $(OUTDIR)

{{range $a := .Apps}}
{{$.P.Binary .}}: {{$a.Dir}}/app.ld {{range .Sources}} {{$.P.ObjectFile .}} {{end}} {{range .Deps}} {{$.P.Library .}} {{end}}
	mkdir -p $(OUTDIR)
	{{$.P.Linker}} {{$.P.LinkFlags $a}} $^
{{end}}

include $(wildcard $(OUTDIR)/*.d)
`))
