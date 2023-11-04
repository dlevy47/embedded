#pragma once

#include "types.hh"

struct Error {
  enum struct Space: u8 {
    CORE = 0b00,
    STD = 0b01,
    APP = 0b10,
    USER = 0b11,
  };

  enum struct CoreError: u16 {
    OK = 0,
  };

  // space is the namespace used for the source and code values.
  Space space:2 { Space::CORE };

  // source represents a source for the error.
  u16 source:14 { 0 };

  // code is the error code.
  u16 code { 0 };

  static const char* space_name(Space s) {
    switch (s) {
      case Space::CORE:
        return "C";
      case Space::STD:
        return "S";
      case Space::APP:
        return "A";
      case Space::USER:
        return "U";
      default:
        return "?";
    }
  }

  operator bool() {
    return code != 0;
  }
};

static_assert(
sizeof(Error) == 4,
"Error size is not 4 bytes");
