#!/bin/sh
go run tools/bdf-dumper/bdf-dumper.go --font-name gfx::fonts::Misaki lib/gfx/fonts/misaki_gothic.bdf lib/gfx/fonts/misaki.glyphs.txt > lib/gfx/fonts/misaki.cc
