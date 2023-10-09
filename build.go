package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"io/fs"
	"os"
	"os/exec"
	"path/filepath"
	"reflect"
	"strings"
	"text/template"
)

var o3 = flag.Bool("o3", false, "whether to optimize build")

type CompileCommand struct {
	Directory string   `json:"directory"`
	Arguments []string `json:"arguments"`
	File      string   `json:"file"`
}

type App struct {
	Dir     string
	Name    string
	Sources []string
	Objects []string
}

func main() {
	flag.Parse()

	wd, err := os.Getwd()
	if err != nil {
		panic(err)
	}

	apps, err := findApps("apps")
	if err != nil {
		panic(err)
	}

	libSources := findSources("lib")

	var libObjects []string
	for _, source := range libSources {
		libObjects = append(libObjects, objectFile(source))
	}

	writeCompileCommands(wd, libSources, apps)

	args := append([]string{"-f", "-"}, flag.Args()...)

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
			"Apps":       apps,
			"LibSources": libSources,
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
}

func writeCompileCommands(wd string, libSources []string, apps []App) {
	var compileCommands []CompileCommand

	for _, source := range libSources {
		object := objectFile(source)

		compileCommands = append(compileCommands, CompileCommand{
			Directory: wd,
			Arguments: []string{
				"clang",
				"-target",
				"armv6m-none-eabi",
				"-I",
				"lib/",
				"-mthumb",
				"-g",
				"-Werror",
				"-c",
				source,
				"-o",
				object,
			},
			File: source,
		})

		fmt.Fprintf(os.Stderr, "%s => %s\n", source, object)
	}

	for _, app := range apps {
		for _, source := range app.Sources {
			object := objectFile(source)

			compileCommands = append(compileCommands, CompileCommand{
				Directory: wd,
				Arguments: []string{
					"clang",
					"-target",
					"armv6m-none-eabi",
					"-I",
					"lib/",
					"-I",
					app.Dir,
					"-mthumb",
					"-g",
					"-Werror",
					"-c",
					source,
					"-o",
					object,
				},
				File: source,
			})

			fmt.Fprintf(os.Stderr, "%s => %s\n", source, object)
		}
	}

	outf, err := os.Create("compile_commands.json")
	if err != nil {
		panic(err)
	}
	defer outf.Close()

	if err := json.NewEncoder(outf).Encode(compileCommands); err != nil {
		panic(err)
	}
}

func asmFile(source string) string {
	return filepath.Join("build", strings.Replace(source, string(os.PathSeparator), "-", -1)+".s")
}

func objectFile(source string) string {
	return filepath.Join("build", strings.Replace(source, string(os.PathSeparator), "-", -1)+".o")
}

func findApps(dirs ...string) ([]App, error) {
	var apps []App
	for _, dir := range dirs {
		entries, err := os.ReadDir(dir)
		if err != nil {
			return nil, err
		}

		for _, entry := range entries {
			appDir := filepath.Join(dir, entry.Name())
			sources := findSources(appDir)

			var objects []string
			for _, source := range sources {
				objects = append(objects, objectFile(source))
			}

			apps = append(apps, App{
				Dir:     appDir,
				Name:    entry.Name(),
				Sources: sources,
				Objects: objects,
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

func concat(args ...any) any {
	if len(args) == 0 {
		return []string{}
	}

	ty := reflect.TypeOf(args[0])
	ret := reflect.MakeSlice(ty, 0, len(args))

	for _, arg := range args {
		if reflect.TypeOf(arg) != ty {
			panic(fmt.Sprintf("invalid concat arg type: got %v want %v", reflect.TypeOf(arg), ty))
		}

		ret = reflect.Append(ret, reflect.ValueOf(arg))
	}

	return ret.Interface()
}

func cflags() string {
	var ret []string

	if *o3 {
		ret = append(ret, "-O3")
	}

	return strings.Join(ret, " ")
}

var sourceExtensions = map[string]bool{
	".c": true,
	".s": true,
}

var makefileTemplate = template.Must(template.New("makefile").Funcs(template.FuncMap{
	"asm":    asmFile,
	"cflags": cflags,
	"object": objectFile,
	"concat": concat,
}).Parse(`
CC=clang
CFLAGS=-target armv6m-none-eabi -I lib/ -c -mthumb -g -Werror -Wno-unused-command-line-argument {{cflags}}
CPPFLAGS=

LD=clang
LDFLAGS=-nostdlib -nodefaultlibs -target armv6m-none-eabi -fno-exceptions -fno-rtti

OUTDIR = build/

all: {{range .Apps}} $(OUTDIR)/{{.Name}} {{end}}
.PHONY: all

{{range .LibSources}}
{{object .}}: {{.}}
	mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(CC) -S -c $(CFLAGS) $(CPPFLAGS) $< -o {{asm .}}
{{end}}

{{range $a := .Apps}}{{range .Sources}}
{{object .}}: {{.}}
	mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) -I {{$a.Dir}} $(CPPFLAGS) $< -o $@
	$(CC) -S -c $(CFLAGS) $(CPPFLAGS) $< -o {{asm .}}
{{end}}{{end}}

clean:
	rm -rf $(OUTDIR)

{{range $a := .Apps}}
$(OUTDIR)/{{.Name}}: {{$a.Dir}}/app.ld {{range .Sources}} {{object .}} {{end}} {{range $.LibSources}} {{object . }} {{end}}
	mkdir -p $(OUTDIR)
	$(LD) $(LDFLAGS) -o $@ $^
{{end}}
`))
