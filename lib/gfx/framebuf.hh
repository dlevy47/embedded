#pragma once

#include "gfx/primitives.hh"
#include "types.hh"

namespace gfx {

template <u16 _width, u16 _height, typename Format>
struct Framebuf {
  static const u16 width = _width;
  static const u16 height = _height;
  static const u8 bpp = Format::bpp;

  static_assert(
    (_width * _height * Format::bpp) % 8 == 0,
    "width * height * bpp must be multiple of 8");

  u8 buf[width * height * Format::bpp / 8] { 0 };

  template <typename OtherFormat, size_t N>
  void blit(
    const Point<i16> at,
    const u8 (&from)[N]) {
  }
};

}
