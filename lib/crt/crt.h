#pragma once

#include "types.h"

struct crt_hal {
  int (*putu8) (
    struct crt_hal* hal,
    u8 x);
};

// Borrowed from clang's stdarg.h files.
typedef __builtin_va_list va_list;

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
/* C23 does not require the second parameter for va_start. */
#define va_start(ap, ...) __builtin_va_start(ap, 0)
#else
/* Versions before C23 do require the second parameter. */
#define va_start(ap, param) __builtin_va_start(ap, param)
#endif
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)

int crt_printf(
  struct crt_hal* hal,
  const char* fmt,
  ...);
