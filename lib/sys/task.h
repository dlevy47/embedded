#pragma once

#include "types.h"

// sys_task_stacksize is the possible sizes for the task stack.
enum sys_task_stacksize {
  SYS_TASK_STACKSIZE_256B = 7,
  SYS_TASK_STACKSIZE_512B,
  SYS_TASK_STACKSIZE_1K,
  SYS_TASK_STACKSIZE_2K,
  SYS_TASK_STACKSIZE_4K,
  SYS_TASK_STACKSIZE_8K,
  SYS_TASK_STACKSIZE_16K,
  SYS_TASK_STACKSIZE_32K,
  SYS_TASK_STACKSIZE_64K,
  SYS_TASK_STACKSIZE_128K,
  SYS_TASK_STACKSIZE_256K,
  SYS_TASK_STACKSIZE_512K,
};

// sys_task_descriptor describes a task. Only metadata for the task is
// contained here; runtime information is in struct sys_task.
struct sys_task_descriptor {
  // name is the name of the task. Only used for debugging and as a key.
  const char* name;

  // desired_stack_size is the desired size of the stack of this task. The
  // actual size of the task's stack will be greater than or equal to this,
  // depending on board/chip constraints.
  duration_t desired_stack_size;

  // entry is the code to start running the task.
  int (*entry) ();
};

// sys_task contains runtime information about the task.
struct sys_task {
  // descriptor is the metadata about this task.
  const struct sys_task_descriptor* descriptor;

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
extern struct sys_task* _sys_currenttask;
