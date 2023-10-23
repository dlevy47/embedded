#pragma once

#include "crt/print.hh"

template <typename HAL>
struct CRT: public HAL {
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
