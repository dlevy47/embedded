#pragma once

namespace std {
namespace assert {

struct False {
  static const bool value = false;
};

struct True {
  static const bool value = true;
};

template <typename T>
struct Ref {
  typedef T& Type;
};

template <typename T, typename U>
struct SameType: False {};

template <typename T>
struct SameType<T, T>: True {};

inline void panic(volatile const char* message) {
  __asm volatile("bkpt #1");

  while (1);
}

}
}
