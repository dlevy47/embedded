#pragma once

#include "types.hh"

struct Error {
  enum Space: u8 {
    SPACE_CORE = 0b00,
    SPACE_STD = 0b01,
    SPACE_APP = 0b10,
    SPACE_USER = 0b11,
  };

  enum CoreError: u16 {
  };

  // space is the namespace used for the source and code values.
  Space space:2 { SPACE_CORE };

  // source represents a source for the error.
  u16 source:14 { 0 };

  // code is the error code.
  u16 code { 0 };

  static const Error OK;
};

static_assert(
  sizeof(Error) == 4,
  "Error size is not 4 bytes");
