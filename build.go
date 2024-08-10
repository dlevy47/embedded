package main

import (
	"os"

	"embedded/tools/build"
)

func main() {
	var stm32l build.STM32L
	var stm32f build.STM32F
	var atsamd51j19 build.ATSAMD51J19

	stm32lLib := build.Lib(stm32l, "lib")
	stm32fLib := build.Lib(stm32f, "lib")
	atsamd51j19Lib := build.Lib(atsamd51j19, "lib")

	targets := []build.Target{
		stm32lLib,
		stm32fLib,
		atsamd51j19Lib,
		build.App(stm32l, "apps/eink-discovery", stm32lLib),
		build.App(stm32f, "apps/parallel-flash-dumper", stm32fLib),
		build.App(atsamd51j19, "apps/pygamer-hello", atsamd51j19Lib),
	}

	wd, err := os.Getwd()
	if err != nil {
		panic(err)
	}

	build.WriteCompileCommands(wd, targets)

	if err := build.Main(targets); err != nil {
		panic(err)
	}
}

