#pragma once

#include "os/task.hh"
#include "std/assert.hh"
#include "sys/isr.hh"
#include "types.hh"

namespace os {

struct NOPDebug {
  template <typename ...Args>
  int print(Args... args) volatile {
    return 0;
  }
};

struct CPUIndex {
  size_t index { 0 };
};

static_assert(
  sizeof(CPUIndex) == 4,
  "CPUIndex must be exactly 4 bytes");

extern "C" inline void* os_scheduler_control = nullptr;
extern "C" inline CPUIndex (*os_scheduler_cpuindex)() = nullptr;

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
    Task* current { &scheduler_task };

    // next must be the second member, as its offset is hardcoded in assembly.
    Task* next { nullptr };
    
    Task* tasks { nullptr };
    size_t count { 0 };

    Task scheduler_task { "_scheduler" };

    Scheduler* self { nullptr };
  } control[HAL::cpu_count];

  // control's size is hardcoded in the assembly routines, so assert it.
  static_assert(
    sizeof(Control) == 44,
    "Control block size incorrect");

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

  static void task_ended(Error err) {
    volatile Control* control =
      &Scheduler::control[HAL::cpu_index().index];
    
    if (err) {
      control->self->Debug::print("task ", control->current->name, " ended with error: ", err, "\r\n");
      std::assert::panic("task ended with error");
    }
    
    control->current->ended = true;
    control->self->yield();
    while (true) {
      __asm volatile ("");
    }
  }

  Scheduler(const Scheduler&) = delete;

  // Delete the move constructor because we make heavy use of internal pointers.
  Scheduler(Scheduler&&) = delete;
};

};
