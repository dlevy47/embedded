#pragma once

#include "crt.hh"
#include "mcu/arm/stm32l0538.hh"
#include "os/scheduler.hh"
#include "std/assert.hh"
#include "std/utf8.hh"

using MCU = mcu::arm::STM32L0538;

struct CRTHAL {
	int print_codepoint(u32 x) {
		u8 bytes[4];
		size_t count = std::utf8::encode(bytes, x);

		if (count == 0) {
			std::assert::panic("failed to encode invalid codepoint");
		}
		
		for (size_t i = 0; i < count; ++i) {
			while (!MCU::USART1->status.transmit_empty);

			MCU::USART1->transmit = bytes[i];
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

enum struct Watermarks: bool {
	Enabled = true,
	Disabled = false,
};

template <Watermarks WatermarksEnabled>
struct SchedulerHAL {
	typedef os::Scheduler<SchedulerHAL> Scheduler;
	typedef os::Task<Scheduler> Task;
	
	static const size_t cpu_count = 1;

	static const u32 SENTINEL = 0xDEADBEEF;
	static const u32 WATERMARK = 0xCBCBCBCB;

	size_t watermark_display_counter { 0 };

	// SchedulerHAL enables the MPU. A base region encompassing all memory is
	// configured first.
	SchedulerHAL() {
	}

	static os::CPUIndex cpu_index() {
		return os::CPUIndex{0};
	}

	static void trigger_pendsv() {
		MCU::SCB->interrupts.pendsv_set = 1;
	}
	
	void lower_pendsv_priority() {
		MCU::SCB->priority3.pendsv = 255;
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

	void check_stack_corruption(const Task* const task) volatile {
		if (task->stack_limit[0] != SENTINEL ||
			task->stack_limit[1] != SENTINEL) {
			std::assert::panic("stack corruption");
		}
	}

	void check_stack_watermark(const Task* const task) volatile {
		if (static_cast<bool>(WatermarksEnabled)) {
			watermark_display_counter = watermark_display_counter + 1;

			if (watermark_display_counter < 30) {
				return;
			}

			watermark_display_counter = 0;
			
			// Start at the third byte because the first two are corruption
			// sentinels.
			size_t watermarked = 2;
			for (; watermarked < task->stack_size; ++watermarked) {
				if (task->stack_limit[watermarked] != WATERMARK) {
					break;
				}
			}

			size_t usage_words = task->stack_size - watermarked;
			size_t usage = usage_words * sizeof(u32);

			_crt.print("[SchedulerHAL]: task ", task->name, " watermark: ",
							"0x", crt::print::Hex{usage}, " (", usage, ") bytes, "
							"0x", crt::print::Hex{usage_words}, " (", usage_words, ") words\r\n");
		}
	}

	void initialize_task(
		Scheduler* scheduler,
		Task* task) {
		volatile u32* stack_top = task->stack_top;

		if (static_cast<bool>(WatermarksEnabled)) {
			volatile u32* cur = task->stack_limit;
			for (size_t i = 0; i < task->stack_size; ++i) {
				++cur;
				*cur = WATERMARK;
			}
		}
		
    // TODO: Align the stack?

    // Initialize this task's stack. Start with the sentinels:
    task->stack_limit[0] = SENTINEL;
    task->stack_limit[1] = SENTINEL;

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

typedef os::Scheduler<SchedulerHAL<Watermarks::Enabled>> Scheduler;
