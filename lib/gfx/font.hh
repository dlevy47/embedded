#pragma once

#include "types.hh"

namespace gfx {

struct Font {
  struct Glyph {
    u32 encoding;

    struct {
      u16 x;
      u16 y;
    } advance;

    struct {
      u16 x;
      u16 y;
      struct {
        i16 x;
        i16 y;
      } offset;
    } bounding_box;

    const u8* bitmap;
    const u16 bitmap_len;
  };
  
  const char* name;
  const u16 point_size;

  const u32 glyph_count;
  const Glyph glyphs[];

  const Glyph* glyph(u32 encoding) const {
    // Binary search.
    u32 left = 0;
    u32 right = glyph_count - 1;
    while (right - left > 1) {
      u32 at = (left + right) / 2;
    	
      if (glyphs[at].encoding == encoding) {
        return &glyphs[at];
        break;
      }

      if (glyphs[at].encoding < encoding) {
        left = at;
      } else {
        right = at;
      }
    }

    if (glyphs[right].encoding == encoding) {
    	return &glyphs[right];
    }

    if (glyphs[left].encoding == encoding) {
    	return &glyphs[left];
    }

    return nullptr;
  }
};

}
