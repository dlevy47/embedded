// bdf-dumper dumps a selected set of glyphs from a BDF font file to arrays of
// C structures of a particular format for embedding into binaries.
package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
	"sort"
	"strconv"
	"strings"
	"text/template"
)

var fontName = flag.String("font-name", "font", "name to use for the font variable")

func main() {
	flag.Parse()

	args := flag.Args()
	if len(args) < 1 {
		panic("provide font file name")
	}

	inf, err := os.Open(args[0])
	if err != nil {
		panic("failed to open font file")
	}
	defer inf.Close()

	font, err := ParseFont(inf)
	if err != nil {
		panic(fmt.Sprintf("failed to parse font file: %v", err))
	}

	fmt.Fprintf(os.Stderr, "read %d glyphs\n", len(font.Glyphs))

	var selectedGlyphs []*Glyph
	if len(args) > 1 {
		glyphFile, err := os.Open(args[1])
		if err != nil {
			panic("failed to open glyph file")
		}
		defer glyphFile.Close()

		seenRunes := make(map[rune]bool)
		skipRunes := map[rune]bool{
			'\n': true,
			'\r': true,
		}

		scanner := bufio.NewScanner(glyphFile)
		scanner.Split(bufio.ScanRunes)
		for scanner.Scan() {
			var rune rune
			for _, r := range scanner.Text() {
				rune = r
				break
			}

			if seenRunes[rune] || skipRunes[rune] {
				continue
			}

			glyph := font.Glyph(uint(rune))
			if glyph == nil {
				panic(fmt.Sprintf("no glyph at %d (%q)", uint(rune), string(rune)))
			}

			selectedGlyphs = append(selectedGlyphs, glyph)
		}
		if err := scanner.Err(); err != nil {
			panic(fmt.Sprintf("failed to read glyph file: %v", err))
		}
	} else {
		for _, g := range font.Glyphs {
			selectedGlyphs = append(selectedGlyphs, g)
		}
	}

	sort.Slice(selectedGlyphs, func(i, j int) bool {
		return selectedGlyphs[i].Encoding < selectedGlyphs[j].Encoding
	})

	data := map[string]any{
		"Font":   font,
		"Glyphs": selectedGlyphs,
		"Name":   *fontName,
	}
	if err := sourceTemplate.Execute(os.Stdout, data); err != nil {
		panic(fmt.Sprintf("failed to execute template: %v", err))
	}
}

func hex(b byte) string {
	return fmt.Sprintf("0x%x", b)
}

var sourceTemplate = template.Must(template.New("source").Funcs(template.FuncMap{
	"hex": hex,
}).Parse(`#include "gfx/font.hh"
#include "gfx/fonts.hh"
	
const gfx::Font {{.Name}} = {
  .name = "{{.Font.Name}}",
  .point_size = {{.Font.Size.Point}},
  .glyph_count = {{len .Glyphs}},
  .glyphs = {{"{"}}{{range .Glyphs}}
  (const gfx::Font::Glyph) {
    .encoding = {{.Encoding}},
    .advance = {
      .x = {{.DeviceWidth.X}},
      .y = {{.DeviceWidth.Y}},
    },
    .bounding_box = {
      .x = {{.BoundingBox.Width}},
      .y = {{.BoundingBox.Height}},
      .offset = {
        .x = {{.BoundingBox.Offset.X}},
        .y = {{.BoundingBox.Offset.Y}},
      },
    },
    .bitmap = (const u8[]) {{"{"}}{{range .Bitmap}}{{hex .}}, {{end}}},
    .bitmap_len = {{len .Bitmap}},
  },{{end}}}
};
`))

type BDFVersion int

const (
	BDFVersion2_1 BDFVersion = iota
	BDFVersion2_2
)

type Font struct {
	Version BDFVersion
	Name    string
	Size    struct {
		Point int
		XDPI  int
		YDPI  int
	}

	// Glyphs is a map from encoding to Glyph.
	Glyphs map[uint]*Glyph

	// GlyphNames is a map from glyph name to encoding.
	GlyphNames map[string]uint
}

type directive struct {
	Directive string
	Args      string
}

func parseDirective(scanner *bufio.Scanner) (*directive, error) {
	notEOF := scanner.Scan()
	if err := scanner.Err(); err != nil {
		return nil, fmt.Errorf("read failed: %w", err)
	}
	if !notEOF {
		return nil, nil
	}

	pieces := strings.SplitN(scanner.Text(), " ", 2)
	ret := &directive{
		Directive: pieces[0],
	}
	if len(pieces) > 1 {
		ret.Args = pieces[1]
	}

	return ret, nil
}

func expectDirective(scanner *bufio.Scanner, dir string) (*directive, error) {
	got, err := parseDirective(scanner)
	if err != nil {
		return nil, err
	}
	if got == nil {
		return nil, nil
	}

	if got.Directive != dir {
		return nil, fmt.Errorf("expected directive %q, got %q", dir, got.Directive)
	}

	return got, nil
}

func ParseFont(r io.Reader) (*Font, error) {
	font := &Font{
		Glyphs:     make(map[uint]*Glyph),
		GlyphNames: make(map[string]uint),
	}

	scanner := bufio.NewScanner(r)

	start, err := expectDirective(scanner, "STARTFONT")
	if err != nil || start == nil {
		return nil, fmt.Errorf("failed to find STARTFONT directive: %w", err)
	}

	startArgs := strings.Split(start.Args, " ")
	if len(startArgs) < 1 {
		return nil, fmt.Errorf("STARTFONT directive has no version")
	}

	switch startArgs[0] {
	case "2.1":
		font.Version = BDFVersion2_1
	case "2.2":
		font.Version = BDFVersion2_2
	default:
		return nil, fmt.Errorf("unsupported BDF version: %q", startArgs[0])
	}

	for {
		d, err := parseDirective(scanner)
		if err != nil {
			return nil, fmt.Errorf("failed to parse directive: %w", err)
		}
		if d == nil {
			break
		}
		if d.Directive == "ENDFONT" {
			break
		}

		switch d.Directive {
		case "SIZE":
			args := strings.Split(d.Args, " ")
			if len(args) < 3 {
				return nil, fmt.Errorf("SIZE directive has incorrect args")
			}

			font.Size.Point, err = strconv.Atoi(args[0])
			if err != nil {
				return nil, fmt.Errorf("SIZE point size unparseable: %w", err)
			}

			font.Size.XDPI, err = strconv.Atoi(args[1])
			if err != nil {
				return nil, fmt.Errorf("SIZE x DPI unparseable: %w", err)
			}

			font.Size.YDPI, err = strconv.Atoi(args[2])
			if err != nil {
				return nil, fmt.Errorf("SIZE y DPI unparseable: %w", err)
			}
		case "FONT":
			font.Name = d.Args
		case "STARTPROPERTIES":
			args := strings.Split(d.Args, " ")
			if len(args) < 1 {
				return nil, fmt.Errorf("STARTPROPERTIES directive has no count")
			}

			count, err := strconv.Atoi(args[0])
			if err != nil {
				return nil, fmt.Errorf("STARTPROPERTIES directive count unparseable: %w", err)
			}

			for i := 0; i < count; i++ {
				scanner.Scan()
				if err := scanner.Err(); err != nil {
					return nil, fmt.Errorf("read failed: %w", err)
				}
			}

			end, err := parseDirective(scanner)
			if err != nil || end == nil {
				return nil, fmt.Errorf("failed to parse ENDPROPERTIES directive: %w", err)
			}
		case "STARTCHAR":
			glyph, err := parseGlyph(scanner, d.Args)
			if err != nil {
				return nil, fmt.Errorf("failed to parse glyph %q: %w", d.Args, err)
			}

			font.Glyphs[glyph.Encoding] = glyph
			font.GlyphNames[glyph.Name] = glyph.Encoding
		}
	}

	return font, nil
}

func (f *Font) Glyph(encoding uint) *Glyph {
	return f.Glyphs[encoding]
}

func (f *Font) GlyphByName(name string) *Glyph {
	encoding, ok := f.GlyphNames[name]
	if !ok {
		return nil
	}

	return f.Glyphs[encoding]
}

type Glyph struct {
	Name          string
	Encoding      uint
	ScalableWidth struct {
		X int
		Y int
	}
	DeviceWidth struct {
		X int
		Y int
	}
	BoundingBox struct {
		Width  int
		Height int
		Offset struct {
			X int
			Y int
		}
	}
	Bitmap []byte
}

func parseGlyph(scanner *bufio.Scanner, name string) (*Glyph, error) {
	glyph := &Glyph{
		Name: name,
	}

	seenBoundingBox := false
	for {
		d, err := parseDirective(scanner)
		if err != nil {
			return nil, fmt.Errorf("failed to parse directive: %w", err)
		}
		if d == nil {
			return nil, fmt.Errorf("unexpected eof while parsing glyph")
		}
		if d.Directive == "ENDCHAR" {
			break
		}

		switch d.Directive {
		case "ENCODING":
			args := strings.Split(d.Args, " ")
			if len(args) < 1 {
				return nil, fmt.Errorf("ENCODING has no arg")
			}

			encoding, err := strconv.Atoi(args[0])
			if err != nil {
				return nil, fmt.Errorf("ENCODING arg unparseable: %w", err)
			}

			glyph.Encoding = uint(encoding)
		case "SWIDTH":
			args := strings.Split(d.Args, " ")
			if len(args) < 2 {
				return nil, fmt.Errorf("SWIDTH has invalid args")
			}

			glyph.ScalableWidth.X, err = strconv.Atoi(args[0])
			if err != nil {
				return nil, fmt.Errorf("SWIDTH x invalid: %w", err)
			}

			glyph.ScalableWidth.Y, err = strconv.Atoi(args[1])
			if err != nil {
				return nil, fmt.Errorf("SWIDTH y invalid: %w", err)
			}
		case "DWIDTH":
			args := strings.Split(d.Args, " ")
			if len(args) < 2 {
				return nil, fmt.Errorf("DWIDTH has invalid args")
			}

			glyph.DeviceWidth.X, err = strconv.Atoi(args[0])
			if err != nil {
				return nil, fmt.Errorf("DWIDTH x invalid: %w", err)
			}

			glyph.DeviceWidth.Y, err = strconv.Atoi(args[1])
			if err != nil {
				return nil, fmt.Errorf("DWIDTH y invalid: %w", err)
			}
		case "BBX":
			args := strings.Split(d.Args, " ")
			if len(args) < 4 {
				return nil, fmt.Errorf("BBX has invalid args")
			}

			glyph.BoundingBox.Width, err = strconv.Atoi(args[0])
			if err != nil {
				return nil, fmt.Errorf("DWIDTH width invalid: %w", err)
			}

			glyph.BoundingBox.Height, err = strconv.Atoi(args[1])
			if err != nil {
				return nil, fmt.Errorf("DWIDTH height invalid: %w", err)
			}

			glyph.BoundingBox.Offset.X, err = strconv.Atoi(args[2])
			if err != nil {
				return nil, fmt.Errorf("DWIDTH offset x invalid: %w", err)
			}

			glyph.BoundingBox.Offset.Y, err = strconv.Atoi(args[3])
			if err != nil {
				return nil, fmt.Errorf("DWIDTH offset y invalid: %w", err)
			}

			seenBoundingBox = true
		case "BITMAP":
			if !seenBoundingBox {
				return nil, fmt.Errorf("BITMAP before BBX")
			}

			expectedByteCountPerRow := glyph.BoundingBox.Width / 8
			if glyph.BoundingBox.Width%8 != 0 {
				expectedByteCountPerRow++
			}

			for i := 0; i < glyph.BoundingBox.Height; i++ {
				notEOF := scanner.Scan()
				if err := scanner.Err(); err != nil {
					return nil, fmt.Errorf("read failed during BITMAP: %w", err)
				}
				if !notEOF {
					return nil, fmt.Errorf("unexpected eof during BITMAP")
				}

				bytes := strings.Split(scanner.Text(), " ")
				if len(bytes) != expectedByteCountPerRow {
					return nil, fmt.Errorf("BITMAP line %d has %d bytes, expected %d", i, len(bytes), expectedByteCountPerRow)
				}

				for _, b := range bytes {
					value, err := strconv.ParseUint(b, 16, 8)
					if err != nil {
						return nil, fmt.Errorf("BITMAP line %d: failed to parse byte %q", i, b)
					}

					glyph.Bitmap = append(glyph.Bitmap, byte(value))
				}
			}
		}
	}

	return glyph, nil
}
