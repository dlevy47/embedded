#ifndef INCLUDED_ISR_H
#define INCLUDED_ISR_H

#include "types.h"

enum sys_isr_irq {
	SYS_ISR_IRQ0 = 15,
};

void sys_isr_default();
void sys_isr_reserved();
void sys_isr_reset();

typedef void (*sys_isr_t)();

// sys_isr_uservector contains user code to run in case of IRQs.
extern sys_isr_t sys_isr_uservector[29];

struct isr_frame {
	// r0 - r3 are stacked by the MCU.
	// Offset: 0x0
	u32 r0;
	u32 r1;
	u32 r2;
	u32 r3;

	// r12 - xPSR are stacked by the MCU.
	// Offset: 0x14
	u32 r12;
	u32 lr;
	u32 pc;
	u32 xpsr;

	// exc_return is the LR value pushed by the MCU upon this frame's ISR entry.
	// Offset: 0x20
	u32 exc_return;

	// sp is the final value of SP after popping the ISR entry stack.
	// Offset: 0x24
	u32 sp;

	// r4 - r11 are manually saved.
	// Offset: 0x28
	u32 r4;
	u32 r5;
	u32 r6;
	u32 r7;
	u32 r8;
	u32 r9;
	u32 r10;
	u32 r11;
};

extern struct isr_frame _sys_isr_syscall_interruptedframe;

void _sys_isr_syscall(const u8 code);

typedef void (*sys_isr_syscall_t)(u8 code);

// sys_isr_syscall contains user code to run to service a syscall interrupt.
extern sys_isr_syscall_t sys_isr_syscall;

#endif
