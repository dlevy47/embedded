#include "gfx/font.hh"
#include "gfx/fonts.hh"
	
const gfx::Font gfx::fonts::Misaki = {
  .name = "-Kadoma-MisakiGothic-Regular-R-Normal--8-80-75-75-C-79-ISO10646-1",
  .point_size = 8,
  .glyph_count = 186,
  .glyphs = {
  (const gfx::Font::Glyph) {
    .encoding = 32,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 0,
      .y = 0,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {},
    .bitmap_len = 0,
  },
  (const gfx::Font::Glyph) {
    .encoding = 33,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 1,
      .y = 6,
      .offset = {
        .x = 1,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x80, 0x80, 0x0, 0x80, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 34,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 2,
      .offset = {
        .x = 0,
        .y = 4,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, },
    .bitmap_len = 2,
  },
  (const gfx::Font::Glyph) {
    .encoding = 35,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xe0, 0xa0, 0xa0, 0xe0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 36,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xe0, 0xc0, 0x60, 0xe0, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 37,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x20, 0x40, 0x80, 0x20, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 38,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0x40, 0xa0, 0x80, 0x60, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 39,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 2,
      .offset = {
        .x = 0,
        .y = 4,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x80, },
    .bitmap_len = 2,
  },
  (const gfx::Font::Glyph) {
    .encoding = 40,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 41,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 42,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 2,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xe0, 0x40, 0xa0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 43,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x40, 0xe0, 0x40, 0x40, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 44,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 2,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x80, },
    .bitmap_len = 2,
  },
  (const gfx::Font::Glyph) {
    .encoding = 45,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 1,
      .offset = {
        .x = 0,
        .y = 2,
      },
    },
    .bitmap = (const u8[]) {0xe0, },
    .bitmap_len = 1,
  },
  (const gfx::Font::Glyph) {
    .encoding = 46,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 1,
      .y = 1,
      .offset = {
        .x = 1,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, },
    .bitmap_len = 1,
  },
  (const gfx::Font::Glyph) {
    .encoding = 48,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0xe0, 0xa0, 0x40, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 49,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xc0, 0x40, 0x40, 0xe0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 50,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0x20, 0x40, 0x80, 0xe0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 51,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0x20, 0x40, 0x20, 0xc0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 52,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x60, 0xa0, 0xe0, 0x20, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 53,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x80, 0xc0, 0x20, 0xc0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 54,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x80, 0xc0, 0xa0, 0x40, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 55,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x20, 0x40, 0x40, 0x40, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 56,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0x40, 0xa0, 0x40, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 57,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0x60, 0x20, 0xc0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 58,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 1,
      .y = 4,
      .offset = {
        .x = 1,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x0, 0x0, 0x80, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 59,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 5,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x0, 0x0, 0x40, 0x80, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 60,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x40, 0x80, 0x40, 0x20, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 61,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 3,
      .offset = {
        .x = 0,
        .y = 1,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x0, 0xe0, },
    .bitmap_len = 3,
  },
  (const gfx::Font::Glyph) {
    .encoding = 62,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, 0x20, 0x40, 0x80, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 64,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0x20, 0x60, 0xa0, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 65,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0xa0, 0xe0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 66,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xc0, 0xa0, 0xa0, 0xc0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 67,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x80, 0x80, 0x80, 0x80, 0x60, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 68,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xa0, 0xa0, 0xa0, 0xc0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 69,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x80, 0xc0, 0x80, 0x80, 0xe0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 70,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x80, 0xc0, 0x80, 0x80, 0x80, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 71,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x80, 0x80, 0xa0, 0xa0, 0x60, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 72,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xa0, 0xe0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 73,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x40, 0x40, 0x40, 0x40, 0xe0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 74,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x20, 0x20, 0x20, 0xa0, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 75,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xc0, 0xa0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 76,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x80, 0x80, 0x80, 0xe0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 77,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xe0, 0xe0, 0xa0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 78,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 79,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0xa0, 0xa0, 0xa0, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 80,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xa0, 0xc0, 0x80, 0x80, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 81,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0xa0, 0xa0, 0xa0, 0x40, 0x20, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 82,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xa0, 0xc0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 83,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x80, 0x40, 0x20, 0x20, 0xc0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 84,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x40, 0x40, 0x40, 0x40, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 85,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xe0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 86,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xa0, 0xa0, 0xc0, 0x80, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 87,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xa0, 0xe0, 0xe0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 88,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0x40, 0x40, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 89,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0x40, 0x40, 0x40, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 90,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x20, 0x40, 0x40, 0x80, 0xe0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 91,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 92,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 3,
      .offset = {
        .x = 0,
        .y = 1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, 0x20, },
    .bitmap_len = 3,
  },
  (const gfx::Font::Glyph) {
    .encoding = 93,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 94,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 2,
      .offset = {
        .x = 0,
        .y = 4,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, },
    .bitmap_len = 2,
  },
  (const gfx::Font::Glyph) {
    .encoding = 95,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 1,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xe0, },
    .bitmap_len = 1,
  },
  (const gfx::Font::Glyph) {
    .encoding = 96,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 2,
      .offset = {
        .x = 1,
        .y = 4,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, },
    .bitmap_len = 2,
  },
  (const gfx::Font::Glyph) {
    .encoding = 97,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0xa0, 0xa0, 0x60, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 98,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0xc0, 0xa0, 0xa0, 0xc0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 99,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x80, 0x80, 0x60, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 100,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x20, 0x60, 0xa0, 0xa0, 0x60, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 101,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0xe0, 0x80, 0x60, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 102,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x40, 0xe0, 0x40, 0x40, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 103,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x60, 0xa0, 0x60, 0x20, 0xc0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 104,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0xc0, 0xa0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 105,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 1,
      .y = 6,
      .offset = {
        .x = 1,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x0, 0x80, 0x80, 0x80, 0x80, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 106,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x0, 0x40, 0x40, 0x40, 0x40, 0x80, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 107,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0xa0, 0xc0, 0xa0, 0xa0, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 108,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 2,
      .y = 6,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 109,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xe0, 0xe0, 0xa0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 110,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xa0, 0xa0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 111,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xa0, 0xa0, 0x40, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 112,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0xa0, 0xa0, 0xc0, 0x80, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 113,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x60, 0xa0, 0xa0, 0x60, 0x20, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 114,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xc0, 0x80, 0x80, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 115,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x60, 0xc0, 0x60, 0xc0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 116,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x40, 0xe0, 0x40, 0x40, 0x60, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 117,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xa0, 0xe0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 118,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xc0, 0x80, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 119,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0xe0, 0xe0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 120,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0x40, 0x40, 0xa0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 121,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 5,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xa0, 0xa0, 0x60, 0x20, 0xc0, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 122,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x20, 0x40, 0xe0, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 123,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x40, 0x40, 0x80, 0x40, 0x40, 0x20, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 124,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 1,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 125,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, 0x40, 0x20, 0x40, 0x40, 0x80, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 126,
    .advance = {
      .x = 4,
      .y = 0,
    },
    .bounding_box = {
      .x = 3,
      .y = 2,
      .offset = {
        .x = 0,
        .y = 2,
      },
    },
    .bitmap = (const u8[]) {0xc0, 0x60, },
    .bitmap_len = 2,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12354,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x7c, 0x20, 0x3c, 0x6a, 0xb2, 0x64, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12356,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 6,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x88, 0x84, 0x82, 0x82, 0x50, 0x20, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12358,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x0, 0x78, 0x84, 0x4, 0x8, 0x70, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12360,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x0, 0xf8, 0x10, 0x30, 0x50, 0x8c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12362,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf4, 0x22, 0x3c, 0x62, 0xa2, 0x6c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12363,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x20, 0xf4, 0x2a, 0x4a, 0x48, 0xb0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12365,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf8, 0x10, 0xfc, 0x48, 0x80, 0x78, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12367,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 5,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x8, 0x10, 0x60, 0x80, 0x60, 0x10, 0x8, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12369,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x88, 0x88, 0xbe, 0x88, 0x88, 0x88, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12371,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 6,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x0, 0x0, 0x40, 0x80, 0x7c, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12373,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x10, 0xfc, 0x8, 0x48, 0x80, 0x78, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12375,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 5,
      .y = 7,
      .offset = {
        .x = 2,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12377,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x8, 0xfe, 0x18, 0x28, 0x18, 0x8, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12380,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x2a, 0x24, 0xfe, 0x24, 0x2c, 0x20, 0x1e, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12381,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x10, 0x20, 0xfc, 0x20, 0x20, 0x18, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12383,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf0, 0x2e, 0x40, 0x48, 0x50, 0x8e, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12385,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0xfc, 0x20, 0x38, 0x44, 0x4, 0x38, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12388,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x3c, 0xc2, 0x2, 0x2, 0x1c, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12390,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x1c, 0xe8, 0x10, 0x20, 0x20, 0x10, 0xc, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12392,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x40, 0x48, 0x30, 0x40, 0x80, 0x7c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12394,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf4, 0x22, 0x44, 0x9c, 0x26, 0x18, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12395,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x9c, 0x80, 0x80, 0x90, 0xa0, 0x9e, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12396,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x8, 0x48, 0x5c, 0x6a, 0xb2, 0xa6, 0x56, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12397,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x2c, 0xf2, 0x22, 0x66, 0xaa, 0x26, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12398,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 6,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x38, 0x54, 0x92, 0xa2, 0x44, 0x18, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12399,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x84, 0x84, 0xbe, 0x84, 0x9c, 0xa4, 0x9a, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12402,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x28, 0xe4, 0x26, 0x44, 0x44, 0x44, 0x38, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12405,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x8, 0x10, 0x10, 0x4c, 0x4a, 0xb2, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12408,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 4,
      .offset = {
        .x = 0,
        .y = 1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x50, 0x88, 0x6, },
    .bitmap_len = 4,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12413,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x84, 0xba, 0x8c, 0xbe, 0x88, 0xbc, 0xba, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12414,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0xfc, 0x10, 0xfc, 0x10, 0xf8, 0xf4, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12415,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x70, 0x10, 0x24, 0x7c, 0xa6, 0xc4, 0x18, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12416,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf4, 0x22, 0x60, 0xa0, 0x62, 0x3c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12417,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x8, 0x48, 0x5c, 0x6a, 0xb2, 0xa2, 0x54, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12418,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf8, 0x40, 0xf8, 0x44, 0x44, 0x38, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12420,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x48, 0x5c, 0xe2, 0x24, 0x20, 0x10, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12422,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0xbc, 0xd2, 0x92, 0xbc, 0x10, 0x20, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12424,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x10, 0x1c, 0x10, 0x70, 0x98, 0x64, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12425,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x60, 0x10, 0x80, 0xb8, 0xc4, 0x4, 0x78, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12426,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 5,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xb0, 0xc8, 0x88, 0x88, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12427,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x10, 0x20, 0x78, 0x84, 0x64, 0x78, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12428,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x2c, 0xf4, 0x24, 0x64, 0xa4, 0x22, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12431,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x2c, 0xf2, 0x22, 0x62, 0xa2, 0x2c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12435,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x10, 0x20, 0x20, 0x50, 0x52, 0x8c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12450,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfc, 0x4, 0x28, 0x30, 0x20, 0x20, 0x40, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12452,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x4, 0x8, 0x10, 0x30, 0xd0, 0x10, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12454,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xfc, 0x84, 0x4, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12456,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x7c, 0x10, 0x10, 0x10, 0xfe, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12458,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x8, 0xfe, 0x8, 0x18, 0x28, 0xc8, 0x18, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12459,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xfc, 0x24, 0x24, 0x24, 0x44, 0x8c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12461,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0xf8, 0x20, 0x20, 0xfc, 0x10, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12463,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x3c, 0x44, 0x84, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12465,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x40, 0x7e, 0x48, 0x88, 0x8, 0x10, 0x20, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12467,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 6,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfc, 0x4, 0x4, 0x4, 0x4, 0xfc, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12469,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x24, 0xfe, 0x24, 0x24, 0x4, 0x8, 0x30, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12471,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, 0x84, 0x44, 0x8, 0x10, 0xe0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12473,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 6,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x7c, 0x4, 0x8, 0x8, 0x34, 0xc2, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12476,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x2a, 0x20, 0xfe, 0x22, 0x24, 0x20, 0x1e, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12477,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x84, 0x44, 0x44, 0x4, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12479,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x3c, 0x44, 0xb4, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12481,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xc, 0x70, 0x10, 0xfe, 0x10, 0x10, 0x20, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12484,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 6,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xa2, 0x52, 0x52, 0x4, 0x8, 0x30, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12486,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x7c, 0x0, 0xfe, 0x10, 0x10, 0x10, 0x20, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12488,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 4,
      .y = 7,
      .offset = {
        .x = 2,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x80, 0xe0, 0x90, 0x80, 0x80, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12490,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x10, 0xfe, 0x10, 0x10, 0x20, 0x40, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12491,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x7c, 0x0, 0x0, 0x0, 0xfe, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12492,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x7c, 0x4, 0x34, 0x8, 0x18, 0x24, 0xc0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12493,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x7c, 0x8, 0x10, 0x34, 0xd2, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12494,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x4, 0x4, 0x4, 0x8, 0x10, 0x20, 0xc0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12495,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 6,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x28, 0x24, 0x24, 0x42, 0x42, 0x82, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12498,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x8c, 0xf0, 0x80, 0x80, 0x7c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12501,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 6,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfc, 0x4, 0x4, 0x8, 0x10, 0x60, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12504,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x50, 0x88, 0x4, 0x2, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12509,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x14, 0x1a, 0xf4, 0x10, 0x54, 0x92, 0x30, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12510,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 6,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfe, 0x2, 0x4, 0x28, 0x10, 0x8, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12511,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 5,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xe0, 0x18, 0x40, 0x30, 0x0, 0xe0, 0x18, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12512,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x10, 0x20, 0x20, 0x48, 0x44, 0xfa, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12513,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x4, 0x4, 0x74, 0x8, 0x14, 0x24, 0xc0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12514,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x20, 0x20, 0xfc, 0x20, 0x20, 0x1c, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12516,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x20, 0x2e, 0xf2, 0x24, 0x10, 0x10, 0x10, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12518,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 5,
      .offset = {
        .x = 0,
        .y = 0,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x8, 0x8, 0x8, 0xfe, },
    .bitmap_len = 5,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12520,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 6,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfc, 0x4, 0x7c, 0x4, 0x4, 0xfc, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12521,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x78, 0x0, 0xfc, 0x4, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12522,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 5,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x88, 0x88, 0x88, 0x88, 0x8, 0x10, 0x60, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12523,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x8, 0x28, 0x28, 0x28, 0x2a, 0x4c, 0x88, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12524,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 5,
      .y = 7,
      .offset = {
        .x = 2,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x80, 0x80, 0x88, 0x90, 0xa0, 0xc0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12527,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 6,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfc, 0x84, 0x4, 0x8, 0x10, 0x60, },
    .bitmap_len = 6,
  },
  (const gfx::Font::Glyph) {
    .encoding = 12531,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 6,
      .y = 7,
      .offset = {
        .x = 1,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x80, 0x40, 0x4, 0x4, 0x8, 0x10, 0xe0, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 22799,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfe, 0x38, 0x38, 0x38, 0x68, 0x10, 0xee, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 22823,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0x10, 0xfe, 0x10, 0x10, 0x28, 0xc6, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 23455,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x10, 0xfe, 0xba, 0x10, 0xfe, 0x10, 0xee, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 27096,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0x54, 0xfe, 0x5c, 0xfe, 0xea, 0x5c, 0x6a, },
    .bitmap_len = 7,
  },
  (const gfx::Font::Glyph) {
    .encoding = 37326,
    .advance = {
      .x = 8,
      .y = 0,
    },
    .bounding_box = {
      .x = 7,
      .y = 7,
      .offset = {
        .x = 0,
        .y = -1,
      },
    },
    .bitmap = (const u8[]) {0xfe, 0xb2, 0xf4, 0xbe, 0xf6, 0x24, 0xfc, },
    .bitmap_len = 7,
  },}
};
