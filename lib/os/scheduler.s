.align 4
.global os_scheduler_contextswitch
.global os_scheduler_cpuindex
.global os_scheduler_control

.thumb_func
@ void os_scheduler_contextswitch()
os_scheduler_contextswitch:
	@ Here, the stack looks like:
	@ sp + 0x1C: xPSR <-- start of automatic exception entry frame
	@ sp + 0x18: PC
	@ sp + 0x14: LR
	@ sp + 0x10: R12
	@ sp + 0x0C: R3
	@ sp + 0x08: R2
	@ sp + 0x04: R1
	@ sp + 0x00: R0

	@ We should be careful to avoid interrupts here.
	cpsid i

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

	@ r0 points to the stack top to save. We need to keep that value around
	@ while we clobber r0 to get the cpu index.
	mov r5, r0

	@ Determine the index of this CPU. On multi-core processors, this will
	@ perform a processor-specific operation to determine the index. On
	@ single-cores, it should just return 0.
	ldr r0, =os_scheduler_cpuindex
	ldr r0, [r0]
	blx r0

	@ bl clobbered lr. Restore it from r4.
	mov lr, r4

	@ r0 now has the cpu index. Use that to compute our CPU's control.
	@ Control blocks are 44 bytes.
	movs r1, #44
	muls r0, r0, r1

	@ r0 += os_scheduler_control
	ldr r1, =os_scheduler_control
	ldr r1, [r1]
	adds r0, r0, r1

	@ r0 is now Control*. We need to load the task's stack pointer (in r5) into
	@ the current task:
	@   r0->current->stack_top = r5
	ldr r1, [r0]  @ r1 = r0->current
	str r5, [r1]  @ *r1 = r5

	@ Before we pop from the next task's stack, overwrite current.
	@   control->current = control->next
	@ r0 is currently &r0->current. next is 4 bytes after.
	adds r1, r0, 4  @ r1 = &control->next
	ldr r2, [r1]    @ r2 = *r1
	str r2, [r0]    @ *(&control->current) = r2

	@ Now that we've saved the current task's stack pointer, we need to get the
	@ next task's stack pointer.
	@   r0 = control->next->stack_top
	@ r1 = &control->next
	ldr r1, [r1]  @ r1 = *r1
	ldr r0, [r1]  @ r0 = *r1

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

	@ Re-enable interrupts...
	cpsie i

	@ And finally leave the exception.
	bx lr
