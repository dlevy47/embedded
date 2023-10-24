#pragma once

#include "types.hh"

namespace std {
namespace utf8 {

inline u32 codepoint(const char** s) {
  enum: u8 {
    ONEBYTE   = 0b00000000,
    TWOBYTE   = 0b11000000,
    THREEBYTE = 0b11100000,
    FOURBYTE  = 0b11110000,
    MASK      = 0b00111111,
  };
  u32 codepoint = static_cast<u32>(**s);
  if (codepoint == 0) {
    return 0;
  }
  
  u8 advance = 1;
  if ((codepoint & FOURBYTE) == FOURBYTE) {
    if (*((*s) + 1) == 0 || *((*s) + 2) == 0 || *((*s) + 3) == 0) {
      goto fail;
    }
    
    codepoint =
      static_cast<u32>(codepoint & ~FOURBYTE) << 18 |
      static_cast<u32>((*((*s) + 1) & MASK)) << 12 |
      static_cast<u32>((*((*s) + 2) & MASK)) << 6 |
      static_cast<u32>((*((*s) + 3) & MASK));

    (*s) += 4;
    return codepoint;
  } else if ((codepoint & THREEBYTE) == THREEBYTE) {
    if (*((*s) + 1) == 0 || *((*s) + 2) == 0) {
      goto fail;
    }

    codepoint =
      static_cast<u32>(codepoint & ~THREEBYTE) << 12 |
      static_cast<u32>((*((*s) + 1) & MASK)) << 6 |
      static_cast<u32>((*((*s) + 2) & MASK));

    (*s) += 3;
    return codepoint;
  } else if ((codepoint & TWOBYTE) == TWOBYTE) {
    if (*((*s) + 1) == 0) {
      goto fail;
    }
    
    codepoint =
      static_cast<u32>(codepoint & ~TWOBYTE) << 6|
      static_cast<u32>((*((*s) + 1) & MASK)); 

    (*s) += 2;
    return codepoint;
  } else if ((codepoint & ONEBYTE) == ONEBYTE) {
    (*s) += 1;
    return codepoint;
	}

fail:
  *s = nullptr;
  return 0;
}

}
}
