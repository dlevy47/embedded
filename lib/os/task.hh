#pragma once

#include "error.hh"
#include "types.hh"

namespace os {

template <typename Scheduler>
struct Task {
  // stack_top must be the first member, as its offset is hardcoded in
  // the assembly routines.
  volatile u32* stack_top;

  // stack_size is the size of this task's stack, in words.
  volatile size_t stack_size;

  volatile u32* const stack_limit;
  
  const char* name;

  bool ended { false };

  Error (*entry) (Scheduler* scheduler);

  template <size_t N>
  Task(
    const char* name,
    u32 (&stack)[N],
    Error (*entry) (Scheduler* s)):
    name(name),
    stack_top(stack + N),
    stack_size(N),
    stack_limit(stack),
    entry(entry) {}

  Task(
    const char* name):
    name(name),
    stack_top(nullptr),
    stack_size(0),
    stack_limit(nullptr),
    entry(nullptr) {}
};

};
