.align 4
.global __aeabi_uidiv
.global __aeabi_uidivmod

.type __aeabi_uidiv, %function
.type __aeabi_uidivmod, %function

@ ARM Thumb asm translation of https://stackoverflow.com/a/12699549.

.thumb_func
@ This code also works for division.
@ u32 __aeabi_uidiv(u32 dividend, u32 divisor)
__aeabi_uidiv:
@ struct {u32 q; u32 r;} __aeabi_uidivmod(u32 dividend, u32 divisor)
__aeabi_uidivmod:
  @ prologue: save r4, r5, r6 on the stack
  push {r4, r5, r6}

  @ r0 = dividend
  @ r1 = divisor
  @ r2 = i

  @ move divisor to r3
  movs r3, r1

  @ divisor != 0?
  bne nonzero  @ bne checks z == 0
  bkpt 0
  bx lr
  
nonzero:
  @ move dividend to r4
  movs r4, r0

  @ r0 = quotient
  @ r1 = remainder
  @ r2 = i
  @ r3 = divisor
  @ r4 = dividend
  @ r5 = scratch
  @ r6 = scratch
  movs r0, #0
  movs r1, #0
  
  movs r2, #0
loop:
  @ i >= 32?
  cmp r2, #32
  bge end

  @ quotient <<= 1;
  lsls r0, #1

  @ remainder <<=1;
  lsls r1, #1

  @ r6 = 31 - i
  movs r6, #31
  subs r6, r2

  @ r5 = 1 << (31 - i)
  movs r5, #1
  lsls r5, r6

  @ r5 = dividend & (1 << (31 - i))
  ands r5, r4

  @ r5 = (dividend & (1 << (31 - i))) >> (31 - i)
  asrs r5, r6

  @ remainder |= r5
  orrs r1, r5

  @ remainder < divisor?
  cmp r1, r3
  blt next

  @ remainder -= divisor
  subs r1, r3

  @ quotient |= 1
  movs r5, #1
  orrs r0, r5

next:
  @ ++i
  adds r2, #1
  b loop

end:
  pop {r4, r5, r6}
  bx lr
