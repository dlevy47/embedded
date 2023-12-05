.align 4
.global __aeabi_memclr
.global __aeabi_memclr4
.global __aeabi_memcpy
.global __aeabi_memcpy4

.type __aeabi_memclr, %function
.type __aeabi_memclr4, %function
.type __aeabi_memcpy, %function
.type __aeabi_memcpy4, %function

.thumb_func
@ void __aeabi_memclr(void* dest, size_t n)
__aeabi_memclr:
  @ NOTE: EABI specifies this method may only corrupt r0-r3.
  @ r0 = dest
  @ r1 = n
  @ r2 = #0
  movs r2, #0

memclr_loop:
  @ *dest = 0
  strb r2, [r0]

  @ ++dest
  adds r0, #1
  
  @ n -= 1
  subs r1, #1

  @ subs updates flags, effectively having done a cmp n, #0 here.
  bgt memclr_loop

  @ return
  bx lr

.thumb_func
@ void __aeabi_memclr4(void* dest, size_t n)
__aeabi_memclr4:
  @ NOTE: EABI specifies this method may only corrupt r0-r3.
  @ r0 = dest
  @ r1 = n
  @ r2 = #0
  movs r2, #0

memclr4_loop:
  @ *dest = 0
  str r2, [r0]

  @ ++dest
  adds r0, #4
  
  @ n -= 4
  subs r1, #4

  @ subs updates flags, effectively having done a cmp n, #0 here.
  bgt memclr4_loop

  @ return
  bx lr

.thumb_func
@ void __aeabi_memcpy(void* dest, const void* src, size_t n)
__aeabi_memcpy:
  @ NOTE: EABI specifies this method may only corrupt r0-r3.
  @ r0 = dest
  @ r1 = src
  @ r2 = n
  @ r3 = scratch

memcpy_loop:
  @ scratch = *src
  ldrb r3, [r1]

  @ *dest = scratch
  strb r3, [r0]

  @ ++src
  adds r1, #1

  @ ++dest
  adds r0, #1
  
  @ n -= 1
  subs r2, #1

  @ subs updates flags, effectively having done a cmp n, #0 here.
  bgt memcpy_loop

  @ return
  bx lr

.thumb_func
@ void __aeabi_memcpy4(void* dest, const void* src, size_t n)
__aeabi_memcpy4:
  @ NOTE: EABI specifies this method may only corrupt r0-r3.
  @ r0 = dest
  @ r1 = src
  @ r2 = n
  @ r3 = scratch

memcpy4_loop:
  @ scratch = *src
  ldr r3, [r1]

  @ *dest = scratch
  str r3, [r0]

  @ ++src
  adds r1, #4

  @ ++dest
  adds r0, #4
  
  @ n -= 4
  subs r2, #4

  @ subs updates flags, effectively having done a cmp n, #0 here.
  bgt memcpy4_loop

  @ return
  bx lr
