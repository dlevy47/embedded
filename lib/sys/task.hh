#pragma once

#include "error.hh"
#include "types.hh"

namespace sys {
namespace scheduler {

template <typename T>
struct Scheduler;

}

namespace task {

// StackSize is the possible sizes for the task stack.
enum struct StackSize {
  STACKSIZE_256B = 256,
  STACKSIZE_512B = 512,
  STACKSIZE_1K = 1024,
  STACKSIZE_2K = 2048,
  STACKSIZE_4K = 4096,
  STACKSIZE_8K = 8192,
  STACKSIZE_16K = 16384,
  STACKSIZE_32K = 32768,
  STACKSIZE_64K = 65536,
};

// Descriptor describes a task. Only metadata for the task is
// contained here; runtime information is in struct sys_task.
template <typename T>
struct Descriptor {
  // name is the name of the task. Only used for debugging and as a key.
  const char* name;

  // desired_stack_size is the desired size of the stack of this task. The
  // actual size of the task's stack will be greater than or equal to this,
  // depending on board/chip constraints.
  StackSize desired_stack_size;

  // entry is the code to start running the task.
  Error (*entry) (sys::scheduler::Scheduler<T>&);
};

// Task contains runtime information about the task.
template <typename T>
struct Task {
  // descriptor is the metadata about this task.
  const struct Descriptor<T> descriptor;

  // stack_size is the actual runtime size of the task's stack.
  size_t stack_size;

  // stack_bottom is the bottom of the task's stack. This is recorded so that
  // the sentinel values can be checked.
  u32* stack_bottom;

  // stack_top is the address of the top of the task's stack. Only updated
  // after this task has been swapped out.
  u32* stack_top;
};

}
}
