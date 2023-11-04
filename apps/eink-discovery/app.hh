#pragma once

#include "crt.hh"
#include "hal/arm/stm32l0538.hh"
#include "os/scheduler.hh"
#include "std/assert.hh"
#include "std/utf8.hh"

namespace mcu = hal::arm::stm32l0538;

struct CRTHAL {
	int print_codepoint(u32 x) {
		u8 bytes[4];
		size_t count = std::utf8::encode(bytes, x);

		if (count == 0) {
			std::assert::panic("failed to encode invalid codepoint");
		}
		
		for (size_t i = 0; i < count; ++i) {
			while (!mcu::USART1->status.transmit_empty);

			mcu::USART1->transmit = bytes[i];
		}
		
		return 0;
	}

	int print_string(const char* s) {
		while (*s) {
			u32 codepoint = std::utf8::codepoint(&s);
			if (s == nullptr) {
				std::assert::panic("failed to decode codepoint");
			}

			int ret = print_codepoint(codepoint);
			if (ret) return ret;
		}

		return 0;
	}
};

typedef crt::CRT<CRTHAL> CRT;

inline CRT _crt;

struct SchedulerHAL {
	typedef os::Scheduler<SchedulerHAL, CRT> Scheduler;
	typedef os::Task<Scheduler> Task;
	
	static const size_t cpu_count = 1;

	static const u32 SENTINEL = 0xDEADBEEF;

	static os::CPUIndex cpu_index() {
		return os::CPUIndex{0};
	}

	static void trigger_pendsv() {
		mcu::SCB->interrupts.pendsv_set = 1;
	}
	
	void lower_pendsv_priority() {
		mcu::SCB->priority3.pendsv = 255;
	}
	
	__attribute__((naked)) void switch_to_process_stack() {
		__asm volatile (
			"mov r3, sp \n"
			"msr psp, r3 \n"
			"movs r3, #2 \n"
			"msr control, r3 \n"
			"isb \n"
			"bx lr \n"
		);
	}
	
	__attribute__((naked)) void switch_to_main_stack() {
    __asm volatile (
    	"mov r1, sp \n"
    	"msr msp, r1 \n"
    	"movs r1, #0 \n"
    	"msr control, r1 \n"
			"bx lr \n"
  	);
	}

	__attribute__((naked)) static void context_switch() {
		__asm volatile (
			"ldr r0, =os_scheduler_contextswitch \n"
			"bx r0 \n"
		);
	}

	bool is_stack_corrupted(Task* task) {
		if (*(task->stack_bottom - 1) != SENTINEL ||
			*(task->stack_bottom - 2) != SENTINEL) {
			return true;
		}

		return false;
	}

	void initialize_task(
		Scheduler* scheduler,
		Task* task) {
		u32* stack_top = task->stack_top;
		
    // TODO: Align the stack?
    // stack_top contains the current top of this task's stack, which is also
    // the bottom of the stack (because it's empty).
    task->stack_bottom = (u32*) stack_top;

    // Initialize this task's stack. Start with the sentinels:
    //   [ stack sentinel 1 ]
    //   [ stack sentinel 2 ]  <-- stack_top
    --stack_top;
    *stack_top = SENTINEL;
    --stack_top;
    *stack_top = SENTINEL;

    // Next, push the basic stack frame, as would have been pushed by the mcu
    // upon exception entry.

    // xPSR: set T in EPSR.
    --stack_top;
    *stack_top = (1 << 24);

    // PC: the entry point of the task.
    --stack_top;
    *stack_top = (u32) task->entry;

    // LR: where to return to: sys_taskended.
    --stack_top;
    *stack_top = (u32) &Scheduler::task_ended;

    // R12, R3, R2, R1, R0
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = (u32) scheduler; // R0: the first argument to entry

    // Next, push a full stack frame. This way we can swap directly into the
    // task to start it.
    // R4 - R11
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;
    --stack_top;
    *stack_top = 0;

    task->stack_top = stack_top;
	}
};

typedef os::Scheduler<SchedulerHAL, CRT> Scheduler;
