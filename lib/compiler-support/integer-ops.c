#include "types.h"

// u32 __aeabi_uidiv(u32 dividend, u32 divisor) {
//   u32 quotient = 0, remainder = 0;
//   i32 i;
//
//   if (divisor == 0) {
//     __asm("bkpt 0");
//     return 0;
//   }
//
//   for (i = 31 ; i >= 0 ; i--)
//   {
//     quotient <<= 1;
//     remainder <<= 1;
//     remainder |= (dividend & (1 << i)) >> i;
//
//     if (remainder >= divisor)
//     {
//       remainder -= divisor;
//       quotient |= 1;
//     }
//   }
//
//   return quotient;
// }
