package build

import "strings"

type Target interface {
	Name() string
	Dir() string
	Sources() []string
	Deps() []string
	Platform() Platform
}

func sanitizePath(dir string) string {
	return strings.ReplaceAll(dir, "/", "-")
}
