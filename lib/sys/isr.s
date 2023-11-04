.align 4
.global sys_isr_sys_irq13
.global sys_sys_vector
.global sys_isr_reserved

_sys_isr_sys_irq:
	ldr r1, =sys_sys_vector
	lsls r0, 2
	adds r0, r1
	ldr r0, [r0]
	cmp r0, #0
	beq _sys_isr_sys_irq_zero
	bx r0

_sys_isr_sys_irq_zero:
	ldr r0, =sys_isr_reserved
	bx r0

.thumb_func
@ void sys_isr_sys_irq13
sys_isr_sys_irq13:
	movs r0, #13
	b _sys_isr_sys_irq
