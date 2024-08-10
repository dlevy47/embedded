package build

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
)

func Main(
	targets []Target,
) error {
	flag.Parse()

	makeArgs := []string{
		"-f",
		"-",
	}

	if *parallel {
		makeArgs = append(makeArgs, "-j")
	}

	args := append(makeArgs, flag.Args()...)

	var apps []app
	var libs []lib

	for _, target := range targets {
		switch x := target.(type) {
		case *app:
			apps = append(apps, *x)
		case *lib:
			libs = append(libs, *x)
		default:
			panic(fmt.Errorf("target %q unknown type", target.Name()))
		}
	}

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
			}
			if err := makefileTemplate.Execute(stdin, data); err != nil {
				fmt.Fprintf(os.Stderr, "failed to execute makefile template: %v", err)
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
		}
		if err := makefileTemplate.Execute(os.Stdout, data); err != nil {
			return fmt.Errorf("failed to execute makefile template: %w", err)
		}
	}

	return nil
}
