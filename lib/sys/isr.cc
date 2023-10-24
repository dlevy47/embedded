#include "isr.hh"

#include "types.hh"
#include "sys/scheduler.hh"

namespace sys {
namespace isr {

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

Frame _sys_isr_syscall_interruptedframe = {0};

ISR user_vector[29] = {nullptr};

#define DEFINE_ISR(num) \
	static void sys_isr_irq ## num() { \
		if (user_vector[num]) { \
			user_vector[num](); \
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
__attribute__((section(".isr.vector"))) ISR sys_isr_vector[44] = {
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
	sys_isr_default, // sys_scheduler_contextswitch,
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

}
}
