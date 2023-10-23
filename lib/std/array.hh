#pragma once

#include "types.h"

namespace std {

template <typename T, size_t N>
struct Array {
  T values[N];
};

};
