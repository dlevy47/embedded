#pragma once

#include "types.h"

// epd_lut is the LUT sent to the EPD on initialization.
extern const u8 epd_lut[90];

// xbm1bpp_lookup is a lookup table from a 1 bit-per-pixel XBM
// bitmap to the two bytes that need to be send to the epd per XBM byte.
extern const u8 xbm1bpp_lookup[256 * 2];
