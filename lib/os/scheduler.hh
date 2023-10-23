#pragma once

#include "os/task.hh"
#include "types.h"

namespace os {

struct Scheduler {
  Task* tasks;
  size_t task_count;

  Scheduler(Task* tasks, size_t task_count):
    tasks(tasks), task_count(task_count) {}

  Scheduler(const Scheduler&) = delete;
  Scheduler(Scheduler&&) = default;
  ~Scheduler() = default;
};

};
