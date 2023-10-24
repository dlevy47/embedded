#pragma once

#include "types.hh"

namespace sys {
namespace task {

// StackSize is the possible sizes for the task stack.
enum struct StackSize {
  STACKSIZE_256B = 7,
  STACKSIZE_512B,
  STACKSIZE_1K,
  STACKSIZE_2K,
  STACKSIZE_4K,
  STACKSIZE_8K,
  STACKSIZE_16K,
  STACKSIZE_32K,
  STACKSIZE_64K,
  STACKSIZE_128K,
  STACKSIZE_256K,
  STACKSIZE_512K,
};

// Descriptor describes a task. Only metadata for the task is
// contained here; runtime information is in struct sys_task.
struct Descriptor {
  // name is the name of the task. Only used for debugging and as a key.
  const char* name;

  // desired_stack_size is the desired size of the stack of this task. The
  // actual size of the task's stack will be greater than or equal to this,
  // depending on board/chip constraints.
  duration_t desired_stack_size;

  // entry is the code to start running the task.
  int (*entry) ();
};

// Task contains runtime information about the task.
struct Task {
  // descriptor is the metadata about this task.
  const struct Descriptor* descriptor;

  // stack_size is the actual runtime size of the task's stack.
  size_t stack_size;

  // stack_bottom is the bottom of the task's stack. This is recorded so that
  // the sentinel values can be checked.
  u32* stack_bottom;

  // stack_top is the address of the top of the task's stack. Only updated
  // after this task has been swapped out.
  u32* stack_top;
};

// _sys_currenttask is the address of the descriptor of the current task.
extern struct Task* _sys_currenttask;

}
}
