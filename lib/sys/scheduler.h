#pragma once

#include "error.h"
#include "sys/task.h"

// sys_tasks is defined by the application. It should end with a task entry
// whose `descriptor` is NULL. SYS_TASKS_END is provided as a convenience for
// that.
// The list of tasks cannot change at runtime.
extern struct sys_task sys_tasks[];

// _sys_scheduler_currenttask is the index of the currently running task in
// the sys_tasks array. This must not be modified except by the application.
extern u32 _sys_scheduler_currenttask;

#define SYS_TASKS_END ((struct sys_task) {.descriptor = NULL})

struct sys_scheduler {
};

// sys_scheduler_init initializes the provided scheduler and the provided
// tasks.
enum error sys_scheduler_init(
  struct sys_scheduler* scheduler,
  struct sys_task* tasks);

// sys_scheduler_contextswitch services the PendSV exception to effect context
// switches. This is defined in asm because it needs access to the values
// stacked by the mcu without interference from the ARM ABI function prologue.
//
// Context switches proceed as follows:
//
// First, the PendSV is triggered by writing to the appropriate bit in SCB. At
// a time decided by the mcu, automatic stacking occurs and hands control to
// this routine.
//
// Second, this routine pushes the values of registers that were not
// automatically stacked. At this point, the task's stack is still the one
// being used, so these pushes will push to that stack.
//
// Next, this routine calls _sys_scheduler_choosetask, which decides on a next
// task to run.
//
// Finally, control returns to sys_scheduler_contextswitch, which restores
// the registers of the task to run, leaving just the automatically stacked
// basic frame on the task's stack. The PC is then loaded with 0xFFFFFFFD to
// cause execution to continue on the task's stack.
void sys_scheduler_contextswitch();

// sys_scheduler_yield tells the scheduler that now is a good time to swap
// in another task.
void sys_scheduler_yield();

void sys_scheduler_loop(
  struct sys_scheduler* scheduler);

void sys_scheduler_yield();
