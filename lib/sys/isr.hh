#pragma once

#include "types.hh"

namespace sys {
namespace isr {

enum struct IRQ: u32 {
	PENDSV = 13,
	IRQ0 = 15,
};

extern void sys_isr_default();
extern "C" void sys_isr_reserved();

// The app.ld linker script specifies sys_isr_reset as the entry point, so 
// we need to extern "C" to avoid name mangling.
extern "C" void sys_isr_reset();

typedef void (*ISR)();

// sys_vector contains the IRQ vector table for the processor.
extern "C" ISR sys_sys_vector[15];

// user_vector contains user code to run in case of IRQs.
extern ISR user_vector[29];

struct Frame {
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

}
}
