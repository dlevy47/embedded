package build

type app struct {
	dir      string
	name     string
	sources  []string
	deps     []string
	platform Platform
}

func (l *app) Name() string {
	return l.name
}

func (l *app) Dir() string {
	return l.dir
}

func (l *app) Sources() []string {
	return l.sources
}

func (l *app) Deps() []string {
	return l.deps
}

func (l *app) Platform() Platform {
	return l.platform
}

func App(platform Platform, dir string, deps ...Target) Target {
	var depDirs []string
	for _, dep := range deps {
		depDirs = append(depDirs, dep.Dir())
	}

	return &app{
		dir:      dir,
		name:     sanitizePath(dir),
		sources:  FindSources(platform, dir),
		deps:     depDirs,
		platform: platform,
	}
}
