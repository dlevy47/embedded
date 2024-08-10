package build

import (
	"flag"
)

var (
	dryRun   = flag.Bool("dry-run", false, "don't build, just print makefile")
	o3       = flag.Bool("o3", false, "whether to optimize build")
	outdir   = flag.String("outdir", "build/", "where to place build artifacts")
	parallel = flag.Bool("j", false, "whether to build with -j")
)
