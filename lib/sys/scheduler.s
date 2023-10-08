.align 4
.global sys_scheduler_contextswitch
.global _sys_scheduler_choosestack
.global _sys_scheduler_switchstacks

.thumb_func
@ void _sys_scheduler_switchstacks(size_t main_stack_top)
_sys_scheduler_switchstacks:
  @ Load PSP with our current stack pointer.
  mov r1, sp
  msr psp, r1

  @ Tell the processor we want to be on the process stack.
  movs r1, #2
  msr control, r1

  @ We have to flush the instructions here.
  isb

  @ Now set the main stack top.
  msr msp, r0

  bx lr

.thumb_func
@ void sys_scheduler_contextswitch()
sys_scheduler_contextswitch:
	@ Here, the stack looks like:
	@ sp + 0x1C: xPSR <-- start of automatic exception entry frame
	@ sp + 0x18: PC
	@ sp + 0x14: LR
	@ sp + 0x10: R12
	@ sp + 0x0C: R3
	@ sp + 0x08: R2
	@ sp + 0x04: R1
	@ sp + 0x00: R0

	@ Grab our task's stack pointer so we can manipulate it.
	@ We can't just use SP here because it points to the handler's stack.
	mrs r0, psp

	@ Make space for 8 registers (stack grows downward).
	subs r0, #32
	
	@ r0 now holds the stack top after pushing the full frame. Copy it into r1
	@ to preserve the value.
	mov r1, r0

	@ Stack the first batch of unautomatically stacked registers.
	stmia r1!, {r4-r7}

	@ stmia on the stm32l0 only supports r0-r7, so we have to copy r8-r11 over.
	mov r4, r8
	mov r5, r9
	mov r6, r10
	mov r7, r11
	stmia r1!, {r4-r7}

	@ At this point, our task's stack has the additional values:
	@ R0 <-- the top of the automatic exception entry frame -->
	@ R11
	@ R10
	@ R9
	@ R8
	@ R7
	@ R6
	@ R5
	@ R4

	@ Save our LR value for exiting exception later.
	mov r4, lr

	@ Jump to C to figure out the next task to execute.
	@ size_t _sys_scheduler_choosestack(size_t current_stack_top)
	bl _sys_scheduler_choosestack

	@ _sys_scheduler_choosestack returns the address of the top of the next stack
	@ to execute. This value is in r0.

	@ We need to inverse the order of operations, so first we grab r8-r11. Right
	@ now, r0 is pointing to the pushed r4, so move it down the stack.
	adds r0, #16

	@ ldmia also only supports r0-r7.
	ldmia r0!, {r4-r7}
	mov r8, r4
	mov r9, r5
	mov r10, r6
	mov r11, r7

	@ Now we can grab the pushed r4-r7. We have to go back to the top of the
	@ stack for them.
	mov r1, r0
	subs r1, #32

	ldmia r1!, {r4-r7}

	@ Now all our context saving is done. We can point psp to our stack...
	msr psp, r0

	@ And finally leave the exception.
	bx lr
