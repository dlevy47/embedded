#pragma once

#include "error.hh"
#include "types.hh"

namespace os {

// struct Task {
//   const char* name;
//
//   u8* stack_top;
//
//   size_t stack_size;
//
//   Error (*entry) ();
//
//   template <size_t N>
//   Task(
//     const char* name,
//     u8 (&stack)[N],
//     Error (*entry) ()):
//     name(name),
//     stack_top(stack + N),
//     stack_size(N),
//     entry(entry) {}
//
//   Task(
//     const char* name):
//     name(name),
//     stack_top(nullptr),
//     stack_size(0),
//     entry(nullptr) {}
// };

template <typename Scheduler>
struct Task {
  // stack_top must be the first member, as its offset is hardcoded in
  // the assembly routines.
  u32* stack_top;

  size_t stack_size;

  u32* stack_bottom;
  
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
    entry(entry) {}

  Task(
    const char* name):
    name(name),
    stack_top(nullptr),
    stack_size(0),
    entry(nullptr) {}
};

};
