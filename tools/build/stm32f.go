package build

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

type STM32F struct{}

var stm32fTags = map[string]bool{
	"stm32f":   true,
	"cortexm0": true,
}

func (STM32F) Tags() map[string]bool {
	return stm32fTags
}

func (STM32F) AssemblyFile(source string) string {
	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".stm32f.s")
}

func (STM32F) DependenciesFile(source string) string {
	if filepath.Ext(source) == ".s" {
		return ""
	}

	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".stm32f.d")
}

func (STM32F) ObjectFile(source string) string {
	return filepath.Join(*outdir, strings.Replace(source, string(os.PathSeparator), "-", -1)+".stm32f.o")
}

func (STM32F) Library(name string) string {
	return filepath.Join(*outdir, fmt.Sprintf("lib%s.stm32f.a", name))
}

func (STM32F) CFlags() []string {
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

func (l STM32F) CCFlags() []string {
	flags := append(l.CFlags(), defaultCFlags()...)
	return append(flags, "--std=c++20", "-fno-exceptions")
}

func (l STM32F) CompileFlags(source string, target Target) string {
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

func (l STM32F) AssembleFlags(source string, target Target) string {
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

func (l STM32F) DependenciesFlags(source string) string {
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

func (l STM32F) LinkFlags(app *app) string {
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

func (l STM32F) Binary(app *app) string {
	return filepath.Join(*outdir, fmt.Sprintf("%s.stm32f.exe", app.name))
}

func (l STM32F) Compiler(source string) string {
	return map[string]string{
		".c":   "clang",
		".cc":  "clang++",
		".cpp": "clang++",
		".s":   "clang",
	}[filepath.Ext(source)]
}

func (l STM32F) Linker() string {
	return "clang"
}
