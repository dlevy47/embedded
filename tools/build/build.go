package build

import (
	"encoding/json"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
	"text/template"

	"github.com/google/shlex"
)

type CompileCommand struct {
	Directory string   `json:"directory"`
	Arguments []string `json:"arguments"`
	File      string   `json:"file"`
}

func WriteCompileCommands(wd string, targets []Target) {
	var commands []CompileCommand

	for _, target := range targets {
		commands = append(commands, compileCommands(target.Platform(), wd, target)...)
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

func FindSources(platform Platform, dirs ...string) []string {
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

			if !sourceExtensions[filepath.Ext(d.Name())] {
				return nil
			}

			name := strings.TrimSuffix(d.Name(), filepath.Ext(d.Name()))

			pieces := strings.Split(name, ".")
			if len(pieces) == 2 {
				tags := strings.Split(pieces[1], ",")
				found := false
				for _, tag := range tags {
					if platform.Tags()[tag] {
						found = true
						break
					}
				}

				if !found {
					return nil
				}
			}

			sources = append(sources, path)
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
	
all: {{range .Apps}} {{.Platform.Binary .}} {{end}}
.PHONY: all

{{range $l := .Libs}}
{{range .Sources}}
{{template "compile" source $l.Platform . $l}}
{{end}}

{{$l.Platform.Library .Name}}: {{range .Sources}} {{$l.Platform.ObjectFile .}} {{end}}
	rm -rf {{$l.Platform.Library .Name}}; ar rcs {{$l.Platform.Library .Name}} $^
	
{{end}}

{{range $a := .Apps}}
{{range .Sources}}
{{template "compile" source $a.Platform . $a}}
{{end}}
{{end}}

clean:
	rm -rf $(OUTDIR)

{{range $a := .Apps}}
{{$a.Platform.Binary .}}: {{$a.Dir}}/app.ld {{range .Sources}} {{$a.Platform.ObjectFile .}} {{end}} {{range .Deps}} {{$a.Platform.Library .}} {{end}}
	mkdir -p $(OUTDIR)
	{{$a.Platform.Linker}} {{$a.Platform.LinkFlags $a}} $^
{{end}}

include $(wildcard $(OUTDIR)/*.d)
`))
