#pragma once

#include "os/task.hh"
#include "std/assert.hh"
#include "sys/isr.hh"
#include "types.hh"

namespace os {

// NOPDebug is an implementation of a Debug type for Scheduler that does
// nothing.
struct NOPDebug {
  template <typename ...Args>
  int print(Args... args) volatile {
    return 0;
  }
};

// CPUIndex is a wrapper around a size_t representing a core index.
struct CPUIndex {
  size_t index { 0 };
};

// CPUIndex must be exactly 4 bytes because of its usage in assembly.
static_assert(
  sizeof(CPUIndex) == 4,
  "CPUIndex must be exactly 4 bytes");

// os_scheduler_control is a pointer to the active Scheduler's static control
// block. It is a void* because the assembly routines do not care about the
// template arguments of Scheduler or Task.
extern "C" inline void* os_scheduler_control = nullptr;

// os_scheduler_cpuindex is a pointer to a function that returns the index of
// the core it's called from. This is required so that the assembly routines can
// access the HAL::cpu_index method of the currently active Scheduler type.
extern "C" inline CPUIndex (*os_scheduler_cpuindex)() = nullptr;

// Scheduler provides facilities for cooperative task switching on single-core
// or symmetric multi-core Cortex M processors. Scheduler makes the following
// assumptions about such a system:
//   * In general, all cores have access to the same memory at the same
//     addresses
//   * Each core has a way to discover which core it is (e.g. through the
//     reading of a specific register)
//   * Each core has a separate interrupt vector, mapped at a writable location
//     in memory
//
// Scheduler objects are intended to be instantiated once per core, all of the
// same type. Multiple instantiations of different types of Schedulers will
// result in a panic. This is required so that the same context switching code
// can be installed and used for each core.
//
// Context switching is accomplished by an assembly ISR for the PendSV
// interrupt. This ISR basically performs two actions:
//   1. Save the context (registers etc) of the current task, and save the
//      address of the current task's stack
//   2. Restore the context of the next task, and set the next task as the
//      current task
// The ISR accesses two global variable pointers to do this:
//   1. `os_scheduler_control`: Points to the static Control block
//      of the instantiated Scheduler types
//   2. `os_scheduler_cpuindex`: Points to a function that returns the CPU
//      index of the current core
// Scheduler sets the values of these pointers in its constructor. If they have
// already been set in such a way that implies a Scheduler of a different type
// has already been instantiated, the constructor will panic. One corrolary of
// this behavior is that an extra step is required to instantiate a new Scheduler
// of a different type: the abovementioned pointers must be reset to `nullptr`
// first.
//
// The context switching ISR does not do the actual work of determing which
// task should be run next. That is done at the C++ level, in the context of a
// task that is yielding control.
//
// Scheduler provides some features that can be optionally used by applications:
//   * Loose stack corruption detection: the provided HAL is given the
//     opportunity to check stack sentinels, if used, at every context switch
//   * Stack watermarking: the provided HAL can watermark tasks' stack usage at
//     every context switch
//
// Scheduler takes two template arguments:
//   * `HAL`: A type that contains methods implementing arch-specific
//     functionality. The specific methods required are detailed in the static
//     asserts below.
//   * `Debug`: A type that can be optionally provided to receive information
//     about Scheduler's scheduling decisions.
template <typename HAL, typename Debug = NOPDebug>
struct Scheduler: public HAL, public Debug {
  typedef os::Task<Scheduler> Task;
  
  // HAL::trigger_pendsv should trigger a PendSV interrupt.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::trigger_pendsv),
      void (*)()>::value,
      "HAL::trigger_pendsv missing");
  
  // HAL::lower_pendsv_priority should lower the PENDSV interrupt priority
  // to the lowest possible priority.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::lower_pendsv_priority),
      void (HAL::*)()>::value,
      "HAL::lower_pendsv_priority missing");
  
  // HAL::switch_to_process_stack switches the stack from the main stack
  // to the process stack.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::switch_to_process_stack),
      void (HAL::*)()>::value,
      "HAL::switch_to_process_stack missing");
  
  // HAL::switch_to_main_stack switches the stack from the process stack
  // to the main stack.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::switch_to_main_stack),
      void (HAL::*)()>::value,
      "HAL::switch_to_main_stack missing");
  
  // HAL::context_switch should switch execution contexts from the current
  // CPU's current task to the next task.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::context_switch),
      void (*)()>::value,
      "HAL::context_switch missing");
  
  // HAL::cpu_count should be a const size_t declaring the number of cores
  // on this CPU.
  static_assert(
    std::assert::SameType<
    decltype(HAL::cpu_count),
      const size_t>::value,
      "HAL::cpu_count missing");
  
  // HAL::cpu_index should return the index of the CPU on which it is called.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::cpu_index),
      CPUIndex (*)()>::value,
      "HAL::cpu_index missing");

  // HAL::initialize_task should initialize the provided task's stack with
  // an initial empty context.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::initialize_task),
      void (HAL::*)(Scheduler*, Task*)>::value,
      "HAL::initialize_task missing");

  // HAL::check_stack_corruption should check the task's stack for corruption.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::check_stack_corruption),
      void (HAL::*)(Task*) volatile>::value,
      "HAL::check_stack_corruption missing");

  // HAL::check_stack_watermark should compute the watermark level for the
  // task, reporting it if desired.
  static_assert(
    std::assert::SameType<
    decltype(&HAL::check_stack_watermark),
      void (HAL::*)(Task*) volatile>::value,
      "HAL::check_stack_watermark missing");

  // control contains the per-cpu information needed for this Scheduler
  // to operate.
  inline static struct Control {
    // current must be the first member, as its offset is hardcoded in assembly.
    // current starts off as the _scheduler task so that its stack is saved
    // correctly.
    Task* current { &scheduler_task };

    // next must be the second member, as its offset is hardcoded in assembly.
    Task* next { nullptr };
    
    // tasks is the list of tasks managed by this Scheduler.
    Task* tasks { nullptr };

    // count is the number of tasks in tasks.
    size_t count { 0 };

    // scheduler_task represents the task that instantiated the Scheduler.
    Task scheduler_task { "_scheduler" };

    // self is the address of the Scheduler for this core.
    Scheduler* self { nullptr };
  } control[HAL::cpu_count];

  // control's size is hardcoded in the assembly routines, so assert it.
  static_assert(
    // If this size changes, the corresponding values in the assembly code must
    // be changed.
    sizeof(Control) == 44,
    "Control block size incorrect");

  // Scheduler initializes a Scheduler to run the provided tasks on this core.
  // It also registers this Scheduler type as the active Scheduler. This
  // constructor will panic if it looks like another Scheduler of a different
  // type has been registered.
  template <size_t TaskN>
  Scheduler(Task (&tasks)[TaskN]) {
    static_assert(
      TaskN > 0,
      "no tasks provided");

    if (os_scheduler_control != nullptr &&
      os_scheduler_control != control) {
      std::assert::panic("duplicate scheduler initialization requested: control");
    }
    
    os_scheduler_control = control;

    if (os_scheduler_cpuindex != nullptr &&
      os_scheduler_cpuindex != &HAL::cpu_index) {
      std::assert::panic("duplicate scheduler initialization requested: cpuindex");
    }
    
    os_scheduler_cpuindex = HAL::cpu_index;

    const CPUIndex cpu_index = HAL::cpu_index();
    if (cpu_index.index >= HAL::cpu_count) {
      std::assert::panic("cpu_index out of range");
    }
    
    if (sys::isr::sys_sys_vector[(u32) sys::isr::IRQ::PENDSV]
      != nullptr) {
      std::assert::panic("scheduler already registered");
    }
    
    sys::isr::sys_sys_vector[(u32) sys::isr::IRQ::PENDSV] =
      &HAL::context_switch;
      
    if (sys::isr::sys_sys_vector[(u32) sys::isr::IRQ::PENDSV]
      != &HAL::context_switch) {
      std::assert::panic("current ISR vector is not writeable");
    }

    // Implementation note: the Scheduler switches to the process stack here to
    // simplify the context switching routines. Without this, the context switcher
    // would need to determine the correct stack to save to or restore from.
    HAL::switch_to_process_stack();

    HAL::lower_pendsv_priority();

    for (size_t i = 0; i < TaskN; ++i) {
      HAL::initialize_task(
        this,
        tasks + i);
    }

    control[cpu_index.index].self = this;
    control[cpu_index.index].tasks = tasks;
    control[cpu_index.index].count = TaskN;
  }

  ~Scheduler() {
    HAL::switch_to_main_stack();
    
    if (sys::isr::sys_sys_vector[(u32) sys::isr::IRQ::PENDSV]
      == nullptr) {
      std::assert::panic("no scheduler registered");
    }
    
    sys::isr::sys_sys_vector[(u32) sys::isr::IRQ::PENDSV] =
      nullptr;
  }

  // run starts the Scheduler-controlled sequence of task executions.
  // It does not return unless all tasks return.
  void run() {
    // run proceeds by starting a context switch to the first task. The context
    // switch routine will save the current stack pointer to the core's
    // scheduler_task.
    control[HAL::cpu_index().index].next = control[HAL::cpu_index().index].tasks;

    HAL::trigger_pendsv();
  }

  void yield() volatile {
    Control* control =
      &this->control[HAL::cpu_index().index];

    // First, check for stack corruption and watermarks.
    for (size_t i = 0; i < control->count; ++i) {
      HAL::check_stack_corruption(&control->tasks[i]);
      HAL::check_stack_watermark(&control->tasks[i]);
    }

    bool all_ended = true;
    for (size_t i = 0; i < control->count; ++i) {
      if (!control->tasks[i].ended) {
        all_ended = false;
        break;
      }
    }

    if (all_ended) {
      control->next = &control->scheduler_task;
      HAL::trigger_pendsv();
      // std::assert::panic("should be unreachable");
      return;
    }

    // TODO: Add real logic here.
    size_t start = 0;
    for (start = 0; start < control->count; ++start) {
      if (control->current == &control->tasks[start]) {
        break;
      }
    }

    for (size_t i = start + 1; i != start; ++i) {
      if (i >= control->count) {
        i = 0;
      }

      if (control->tasks[i].ended) {
        continue;
      }

      control->next = &control->tasks[i];
      Debug::print("next task: ", control->next->name, " ",
                   "stack top: ", control->next->stack_top, "\r\n");
      
      HAL::trigger_pendsv();
      break;
    }
  }

  // task_ended is the function that is set as the return address of all tasks.
  // When a task ends, control passes to task_ended, and the return value of
  // that task ends up as the first argument to this function (because the
  // return value of the task is r0, and the first argument is also r0).
  //
  // task_ended does a bit of bookkeeping to mark the task as ended, and then
  // enters an infinite loop.
  static void task_ended(Error err) {
    volatile Control* control =
      &Scheduler::control[HAL::cpu_index().index];
    
    if (err) {
      control->self->Debug::print("task ", control->current->name, " ended with error: ", err, "\r\n");
      std::assert::panic("task ended with error");
    }
    
    control->current->ended = true;
    control->self->yield();

    // PendSV is not necessarily immediately invoked, so we need an infinite
    // loop here to spin while we wait.

    // This loop must include an empty __asm statement so that the compiler
    // doesn't optimize it away.
    while (true) {
      __asm volatile ("");
    }
  }

  // Delete the copy constructor to prevent multiple Schedulers per core.
  Scheduler(const Scheduler&) = delete;

  // Delete the move constructor because we make heavy use of internal pointers.
  Scheduler(Scheduler&&) = delete;
};

};
