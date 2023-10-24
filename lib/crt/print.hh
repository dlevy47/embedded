#pragma once

#include "std/assert.hh"
#include "types.hh"

namespace crt {
namespace print {

// Print is a CRT mixin to provide formatted output. Print provides the print
// method, which takes a variable number of arguments.
template <typename HAL>
struct Print: public HAL {
  static_assert(
    std::assert::SameType<
      decltype(&HAL::print_u8),
      int (HAL::*)(u8)>::value,
    "HAL::print_u8 missing");
  
  static_assert(
    std::assert::SameType<
      decltype(&HAL::print_string),
      int (HAL::*)(const char*)>::value,
    "HAL::print_string missing");
  
  int print() {
    return 0;
  }

  template <typename... Args>
  int print(const char* s, Args... args) {
    int ret = HAL::print_string(s);
    if (ret) return ret;

    return print(args...);
  }

  template <typename... Args>
  int print(u32 u, Args... args) {
    u32 div = 1;
    while ((u / div) >= 10) {
      div *= 10;
    }

    while (div > 0) {
      u32 digit = u / div;
      u -= digit * div;
      div /= 10;

      int ret = HAL::print_u8('0' + digit);
      if (ret) return ret;
    }

    return print(args...);
  }
};

}
}
