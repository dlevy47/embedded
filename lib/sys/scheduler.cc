#include "scheduler.hh"

#include "types.hh"
#include "hal/arm/registers.hh"

namespace sys {
namespace scheduler {

u32 _sys_scheduler_currenttask = 0;

// ld_stack_top is the address of the top of the OS stack. Its value is set
// in the linker script.
extern u8* const ld_stack_top;

// _sys_stacksentinel_1 and _sys_stacksentinel_2 are special values at the
// bottom of task stacks used to detect stack overflows.
static const u32 _sys_stacksentinel_1 = 0xDEADBEEF;
static const u32 _sys_stacksentinel_2 = 0x8BADF00D;

static void sys_taskended() {
  // Just spin.
  while (1) {
    // sys_scheduler_yield();
  }
}

// _sys_scheduler_switchstacks switches to the process stack.
extern void _sys_scheduler_switchstacks();

Error sys_scheduler_init(
  Scheduler* scheduler,
  task::Task* tasks) {
  // First, switch over to a PSP. Stay in privileged mode.
  _sys_scheduler_switchstacks();
  
  // Place and init task stacks.

  // Start our task stacks after our OS stack.
  // Stacks grow downwards according to the ARM ABI.
  u32* stack_top = (u32*) (ld_stack_top - 256);
  
  while (tasks->descriptor) {
    Error err;

    // TODO: Align the stack?
    tasks->stack_size = tasks->descriptor->desired_stack_size;

    // stack_top contains the current top of this task's stack, which is also
    // the bottom of the stack (because it's empty).
    tasks->stack_bottom = (u32*) stack_top;

    // Initialize this task's stack. Start with the sentinels:
    //   [ stack sentinel 1 ]
    //   [ stack sentinel 2 ]  <-- stack_top
    --stack_top;
    *stack_top = _sys_stacksentinel_1;
    --stack_top;
    *stack_top = _sys_stacksentinel_2;

    // Next, push the basic stack frame, as would have been pushed by the mcu
    // upon exception entry.

    // xPSR: set T in EPSR.
    --stack_top;
    *stack_top = (1 << 24);

    // PC: the entry point of the task.
    --stack_top;
    *stack_top = (u32) tasks->descriptor->entry;

    // LR: where to return to: sys_taskended.
    --stack_top;
    *stack_top = (u32) sys_taskended;

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
    *stack_top = 0;

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

    ++tasks;
  }

  // At this point, all stacks are ready to go: this stack (the main stack) has
  // no pushed stack frame, while all other tasks have a process stack as if
  // they were switched from at the very beginning of their entry points
  // (before even the prologue). To kick everything off, we'll pick a task
  // (probably the first one) and then switch to it. sys_scheduler_loop will
  // do that.

  return Error::OK;
}

size_t _sys_scheduler_choosestack(size_t current_stack_top) {
  return current_stack_top;
}

void sys_scheduler_yield() {
  // TODO: Complete.
}

void sys_scheduler_loop(
  struct sys_scheduler* scheduler) {
  while (1) {
  }
}

}
}
