#include "isr.h"

#include "types.h"
#include "sys/scheduler.h"

void sys_isr_default() {
	while(1);
}

void sys_isr_reserved() {
	while(1);
}

static void sys_isr_nmi() {
	while(1);
}

static void sys_isr_hardfault() {
	while(1);
}

struct isr_frame _sys_isr_syscall_interruptedframe = {0};

extern void _sys_isr_syscall_jumptoframe(const struct isr_frame* frame);

void _sys_isr_syscall(const u8 syscode) {
	_sys_isr_syscall_jumptoframe(&_sys_isr_syscall_interruptedframe);
	return;
	/*
	// The code provided to the SVC instruction is the byte at [[$SP + 40] - 2].
	// 32: 16 from entry stanza, 24 from pushed stack frame (mcu.programming 2.3.6).
	u32 code = 0;
	asm (
		"MOV %0, SP"
		: "=r" (code)
		);

	if (sys_isr_syscall) {
		// NOTE: this pointer arithmetic is fragile, and can become incorrect if this
		// function is modified.
		return sys_isr_syscall(* (u8*)(*(u32*)(code + 40) - 2));
	}

	sys_isr_default(); // */
}

extern void _sys_isr_syscall2();

sys_isr_t sys_isr_uservector[29] = {NULL};

#define DEFINE_ISR(num) \
	static void sys_isr_irq ## num() { \
		if (sys_isr_uservector[num]) { \
			sys_isr_uservector[num](); \
		} else { \
			sys_isr_default(); \
		} \
	}

DEFINE_ISR(0);
DEFINE_ISR(1);
DEFINE_ISR(2);
DEFINE_ISR(3);
DEFINE_ISR(4);
DEFINE_ISR(5);
DEFINE_ISR(6);
DEFINE_ISR(7);
DEFINE_ISR(8);
DEFINE_ISR(9);
DEFINE_ISR(10);
DEFINE_ISR(11);
DEFINE_ISR(12);
DEFINE_ISR(13);
DEFINE_ISR(14);
DEFINE_ISR(15);
DEFINE_ISR(16);
DEFINE_ISR(17);
DEFINE_ISR(18);
DEFINE_ISR(19);
DEFINE_ISR(20);
DEFINE_ISR(21);
DEFINE_ISR(22);
DEFINE_ISR(23);
DEFINE_ISR(24);
DEFINE_ISR(25);
DEFINE_ISR(26);
DEFINE_ISR(27);
DEFINE_ISR(28);

// Interrupt table is defined at mcu.reference 12.3.
__attribute__((section(".isr.vector"))) sys_isr_t sys_isr_vector[44] = {
	// What would be the first interrupt (at 0x0), is really the stack top, set in the linker script.
	sys_isr_reset,
	sys_isr_nmi,
	sys_isr_hardfault,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_isr_default,
	sys_isr_reserved,
	sys_isr_reserved,
	sys_scheduler_contextswitch,
	sys_isr_default,


	sys_isr_irq0,
	sys_isr_irq1,
	sys_isr_irq2,
	sys_isr_irq3,
	sys_isr_irq4,
	sys_isr_irq5,
	sys_isr_irq6,
	sys_isr_irq7,
	sys_isr_irq8,
	sys_isr_irq9,
	sys_isr_irq10,
	sys_isr_irq11,
	sys_isr_irq12,
	sys_isr_irq13,
	sys_isr_irq14,
	sys_isr_irq15,
	sys_isr_irq16,
	sys_isr_irq17,
	sys_isr_irq18,
	sys_isr_irq19,
	sys_isr_irq20,
	sys_isr_irq21,
	sys_isr_irq22,
	sys_isr_irq23,
	sys_isr_irq24,
	sys_isr_irq25,
	sys_isr_irq26,
	sys_isr_irq27,
	sys_isr_irq28,
};

sys_isr_syscall_t sys_isr_syscall = NULL;
