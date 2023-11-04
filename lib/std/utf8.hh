#pragma once

#include "types.hh"

namespace std {
namespace utf8 {

enum: u8 {
  ONEBYTE   = 0b00000000,
  TWOBYTE   = 0b11000000,
  THREEBYTE = 0b11100000,
  FOURBYTE  = 0b11110000,
  MASK      = 0b00111111,
  CONTINUE  = 0b10000000,
};

inline size_t encode(
  u8 (&bytes)[4],
  u32 codepoint) {
  if (codepoint >= 0x0 && codepoint < 0x80) {
    bytes[0] = static_cast<u8>(codepoint);
    
    return 1;
  } else if (codepoint >= 0x80 && codepoint < 0x800) {
    bytes[0] = TWOBYTE | (static_cast<u8>(codepoint >> 6) & 0b11111);
    bytes[1] = CONTINUE | (static_cast<u8>(codepoint) & MASK);
    
    return 2;
  } else if (codepoint >= 0x800 && codepoint < 0x10000) {
    bytes[0] = THREEBYTE | (static_cast<u8>(codepoint >> 12) & 0b1111);
    bytes[1] = CONTINUE | (static_cast<u8>(codepoint >> 6) & MASK);
    bytes[2] = CONTINUE | (static_cast<u8>(codepoint) & MASK);
    
    return 3;
  } else if (codepoint >= 0x10000 && codepoint < 0x11000) {
    bytes[0] = FOURBYTE | (static_cast<u8>(codepoint >> 18) & 0b111);
    bytes[1] = CONTINUE | (static_cast<u8>(codepoint >> 12) & MASK);
    bytes[2] = CONTINUE | (static_cast<u8>(codepoint >> 6) & MASK);
    bytes[3] = CONTINUE | (static_cast<u8>(codepoint) & MASK);
    
    return 4;
  }
  
  return 0;
}

inline u32 codepoint(const char** s) {
  u32 codepoint = static_cast<u32>(**s);
  if (codepoint == 0) {
    return 0;
  }
  
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
