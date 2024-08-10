package build

type lib struct {
	dir      string
	name     string
	sources  []string
	deps     []string
	platform Platform
}

func (l *lib) Name() string {
	return l.name
}

func (l *lib) Dir() string {
	return l.dir
}

func (l *lib) Sources() []string {
	return l.sources
}

func (l *lib) Deps() []string {
	return l.deps
}

func (l *lib) Platform() Platform {
	return l.platform
}

func Lib(platform Platform, dir string, deps ...Target) Target {
	var depDirs []string
	for _, dep := range deps {
		depDirs = append(depDirs, dep.Dir())
	}

	return &lib{
		dir:      dir,
		name:     sanitizePath(dir),
		sources:  FindSources(platform, dir),
		deps:     depDirs,
		platform: platform,
	}
}
