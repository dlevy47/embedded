#pragma once

namespace gfx {

template <typename T>
struct Point {
  T x;
  T y;
};

template <typename T>
struct Rect {
  Point<T> top_left;
  
  Point<T> bottom_right;
};

}
