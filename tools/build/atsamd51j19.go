package build

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

type ATSAMD51J19 struct{}

var atsamd51j19Tags = map[string]bool{
	"atsamd51j19": true,
	"cortexm4f":   true,
}

func (ATSAMD51J19) Tags() map[string]bool {
	return atsamd51j19Tags
}

func (ATSAMD51J19) AssemblyFile(source string) string {
	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".atsamd51j19.s")
}

func (ATSAMD51J19) DependenciesFile(source string) string {
	if filepath.Ext(source) == ".s" {
		return ""
	}

	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".atsamd51j19.d")
}

func (ATSAMD51J19) ObjectFile(source string) string {
	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".atsamd51j19.o")
}

func (ATSAMD51J19) Library(name string) string {
	return filepath.Join(*outdir, fmt.Sprintf("lib%s.atsamd51j19.a", name))
}

func (ATSAMD51J19) CFlags() []string {
	return append([]string{
		"-target",
		"armv7em-none-eabi",
		"-mthumb",
		"-g",
		"-Werror",
		"-nostdlib",
		"-nodefaultlibs",
		"-Wno-unused-command-line-argument",
	}, defaultCFlags()...)
}

func (l ATSAMD51J19) CCFlags() []string {
	flags := append(l.CFlags(), defaultCFlags()...)
	return append(flags, "--std=c++20", "-fno-exceptions")
}

func (l ATSAMD51J19) CompileFlags(source string, target Target) string {
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

func (l ATSAMD51J19) AssembleFlags(source string, target Target) string {
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

func (l ATSAMD51J19) DependenciesFlags(source string) string {
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

func (l ATSAMD51J19) LinkFlags(app *app) string {
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

func (l ATSAMD51J19) Binary(app *app) string {
	return filepath.Join(*outdir, fmt.Sprintf("%s.atsamd51j19.exe", app.name))
}

func (l ATSAMD51J19) Compiler(source string) string {
	return map[string]string{
		".c":   "clang",
		".cc":  "clang++",
		".cpp": "clang++",
		".s":   "clang",
	}[filepath.Ext(source)]
}

func (l ATSAMD51J19) Linker() string {
	return "clang"
}
