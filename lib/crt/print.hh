#pragma once

#include "types.h"

namespace crt {

template <typename HAL>
int print(HAL out);

template <typename HAL, typename... Args>
int print(HAL out, const char* s, Args... args);

template <typename HAL, typename... Args>
int print(HAL out, u32 u, Args... args);

template <typename HAL>
int print(HAL out) {
  return 0;
}

template <typename HAL, typename... Args>
int print(HAL out, const char* s, Args... args) {
  int ret = out.puts(s);
  if (ret) return ret;

  return print(out, args...);
}

template <typename HAL, typename... Args>
int print(HAL out, u32 u, Args... args) {
  u32 div = 1;
  while ((u / div) >= 10) {
    div *= 10;
  }

  while (u > 0) {
    u32 digit = u / div;
    u -= digit * div;
    div /= 10;

    int ret = out.putu8('0' + digit);
    if (ret) return ret;
  }

  return print(out, args...);
}

};
