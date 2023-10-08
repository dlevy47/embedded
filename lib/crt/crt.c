#include "crt/crt.h"

static int crt_printf_format(
  struct crt_hal* hal,
  const char** fmt,
  va_list ap) {
  switch (**fmt) {
    case '%': {
      return hal->putu8(
        hal,
        '%');
    } break;
      
    case 'u': {
      u32 u = va_arg(ap, u32);

      u32 div = 1;
      while ((u / div) >= 10) {
        div *= 10;
      }

      while (u > 0) {
        u32 digit = u / div;
        u -= digit * div;
        div /= 10;

        int ret = hal->putu8(
          hal,
          '0' + digit);
        if (ret) return ret;
      }
    } return 0;
    default: {
      return 1;
    } break;
  }

  return 0;
}

int crt_printf(
  struct crt_hal* hal,
  const char* fmt,
  ...) {
  va_list ap;
  va_start(ap, fmt);

  while (*fmt) {
    switch (*fmt) {
      case '%': {
        ++fmt;
        
        int ret = crt_printf_format(
          hal,
          &fmt,
          ap);

        if (ret) return ret;
      } break;
        
      default: {
        int ret = hal->putu8(hal, *fmt);
        
        if (ret) return ret;
      } break;
    }

    ++fmt;
  }

  va_end(ap);
  return 0;
}
