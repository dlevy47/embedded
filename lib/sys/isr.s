.align 4
.global _sys_isr_syscall2
.global _sys_isr_syscall_jumptoframe

.thumb_func
@ void _sys_isr_syscall_jumptoframe(const struct isr_frame* frame);
_sys_isr_syscall_jumptoframe:
	@ frame is in r0, according to the calling convention.

	@ First, restore the SP we saved.
	ldr r2, [r0, #0x24]
	mov sp, r2

	@ Now, restore the stacked ISR entry frame.
	ldr r2, [r0, #0x1C]
	push {r2}
	ldr r2, [r0, #0x18]
	push {r2}
	ldr r2, [r0, #0x14]
	push {r2}
	ldr r2, [r0, #0x10]
	push {r2}
	ldr r2, [r0, #0x0C]
	push {r2}
	ldr r2, [r0, #0x08]
	push {r2}
	ldr r2, [r0, #0x04]
	push {r2}
	ldr r2, [r0, #0x00]
	push {r2}

	@ Then, restore our manually saved registers.
	ldr r4, [r0, #0x28]
	ldr r5, [r0, #0x2C]
	ldr r6, [r0, #0x30]
	ldr r7, [r0, #0x34]

	ldr r1, [r0, #0x38]
	mov r8, r1
	ldr r1, [r0, #0x3C]
	mov r9, r1
	ldr r1, [r0, #0x40]
	mov r10, r1
	ldr r1, [r0, #0x44]
	mov r11, r1

	@ Finally, complete exception handling.
	ldr r0, [r0, #0x20]
	push {r0}
	pop {pc}

.thumb_func
_sys_isr_syscall2:
	@ Here, the stack looks like:
	@ sp + 0x24: code
	@ sp + 0x20: &_sys_isr_syscall_interruptedframe
	@ sp + 0x1C: xPSR <-- start of automatic exception entry frame
	@ sp + 0x18: PC
	@ sp + 0x14: LR
	@ sp + 0x10: R12
	@ sp + 0x0C: R3
	@ sp + 0x08: R2
	@ sp + 0x04: R1
	@ sp + 0x00: R0
	
	@ Stick LR into r3.
	push {lr}
	pop {r3}

	@ At this point, SP is pointing to the top of the pushed frame.
	@ That means that our destination frame struct address is at SP + 0x20...
	ldr r1, [sp, #0x20]

	@ And our syscall code is at SP + 0x24.
	ldr r0, [sp, #0x24]
	
	@ Now pop the isr frame info into our destination struct.
	pop {r2}
	str r2, [r1, #0x00]
	pop {r2}
	str r2, [r1, #0x04]
	pop {r2}
	str r2, [r1, #0x08]
	pop {r2}
	str r2, [r1, #0x0C]
	pop {r2}
	str r2, [r1, #0x10]
	pop {r2}
	str r2, [r1, #0x14]
	pop {r2}
	str r2, [r1, #0x18]
	pop {r2}
	str r2, [r1, #0x1C]
	str r3, [r1, #0x20]

	@ sp is now at the value we need to eventually restore it to.
	mov r3, sp
	str r3, [r1, #0x24]

	@ Save our manual registers.
	str r4, [r1, #0x28]
	str r5, [r1, #0x2C]
	str r6, [r1, #0x30]
	str r7, [r1, #0x34]

	mov r2, r8
	push {r2}
	mov r2, r9
	push {r2}
	mov r2, r10
	push {r2}
	mov r2, r11
	push {r2}

	pop {r3}
	str r3, [r1, #0x44]
	pop {r3}
	str r3, [r1, #0x40]
	pop {r3}
	str r3, [r1, #0x3C]
	pop {r3}
	str r3, [r1, #0x38]
	
	@ Call the OS-level syscall handler.
	@ Calling convention: first argument is in r0 (already loaded with syscall code), second in r1.
	@ _sys_isr_syscall must either call _sys_isr_syscall_jumptoframe, or halt.
	b _sys_isr_syscall
	nop
