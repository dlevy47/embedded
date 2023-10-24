#pragma once

#include "types.hh"

namespace hal {
namespace arm {

struct SCB {
  // Offset: 0x00
  u32 cpuid;

  // Offset: 0x04
  struct {
    u8 active_exception:8;
    u8 _reserved1:3;
    u8 highest_pending_exception:8;
    u8 _reserved2:1;
    u8 interrupt_pending:1;
    u8 isr_preempt:1;
    u8 _reserved3:1;
    u8 systick_clear:1;
    u8 systick_set:1;
    u8 pendsv_clear:1;
    u8 pendsv_set:1;
    u8 _reserved4:2;
    u8 nmi_set:1;
  } interrupts;
};

}
}
