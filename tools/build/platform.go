package build

type Platform interface {
	Tags() map[string]bool

	AssemblyFile(source string) string
	DependenciesFile(source string) string
	ObjectFile(source string) string
	Library(name string) string

	CompileFlags(source string, target Target) string
	AssembleFlags(source string, target Target) string
	DependenciesFlags(source string) string
	LinkFlags(app *app) string

	Binary(app *app) string

	Compiler(source string) string
	Linker() string
}
