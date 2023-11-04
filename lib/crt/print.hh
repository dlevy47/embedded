#pragma once

#include "error.hh"
#include "std/assert.hh"
#include "types.hh"

namespace crt {
namespace print {

template <typename T>
struct Hex {
  T value;
};

template <typename T>
struct Pointer {
  const T* value;
};

// Print is a CRT mixin to provide formatted output. Print provides the print
// method, which takes a variable number of arguments.
template <typename HAL>
struct Print: public HAL {
  // HAL::print_codepoint should print a single unicode codepoint.
  static_assert(
    std::assert::SameType<
      decltype(&HAL::print_codepoint),
      int (HAL::*)(u32)>::value,
    "HAL::print_codepoint missing");
  
  // HAL::print_string should print a null terminated utf8 string. This is provided
  // as a separate method in case optimizations (such as DMA) are available.
  static_assert(
    std::assert::SameType<
      decltype(&HAL::print_string),
      int (HAL::*)(const char*)>::value,
    "HAL::print_string missing");
  
  // Base case.
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
  int print(Error err, Args... args) {
    return print(
      Error::space_name(err.space), ":",
      Hex{err.source}, ":",
      Hex{err.code}, args...);
  }
  
  template <typename U, typename... FArgs, typename... Args>
  int print(U (*p)(FArgs...), Args... args) {
    return print(Pointer{(const void*) p}, args...);
  }
  
  template <typename T, typename... Args>
  int print(const T* p, Args... args) {
    return print(Pointer{p}, args...);
  }
  
  template <typename T, typename... Args>
  int print(Pointer<T> h, Args... args) {
    print("0x");

    return print(Hex<u32>{(u32) h.value}, args...);
  }

  template <typename T, typename... Args>
  int print(Hex<T> h, Args... args) {
    u32 u = h.value;
    
    u32 div = 1;
    while ((u / div) >= 16) {
      div *= 16;
    }

    while (div > 0) {
      u32 digit = u / div;
      u -= digit * div;
      div /= 16;

      int ret = 0;
      if (digit < 10) {
        ret = HAL::print_codepoint('0' + digit);
      } else {
        ret = HAL::print_codepoint('A' + digit - 10);
      }

      if (ret) return ret;
    }

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

      int ret = HAL::print_codepoint('0' + digit);
      if (ret) return ret;
    }

    return print(args...);
  }
};

}
}
