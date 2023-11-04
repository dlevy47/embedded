#pragma once

#include "types.hh"

namespace hal {
namespace arm {

struct SCB {
  // Offset: 0x00
  u32 cpuid;

  // Offset: 0x04
  struct {
    u32 active_exception:9;
    u32 _reserved1:3;
    u32 highest_pending_exception:9;
    u32 _reserved2:1;
    u32 interrupt_pending:1;
    u32 isr_preempt:1;
    u32 _reserved3:1;
    u32 systick_clear:1;
    u32 systick_set:1;
    u32 pendsv_clear:1;
    u32 pendsv_set:1;
    u32 _reserved4:2;
    u32 nmi_set:1;
  } interrupts;

  // Offset: 0x08
  u32 vtor;

  // Offset: 0x0C
  u32 aircr;

  // Offset: 0x10
  u32 scr;

  // Offset: 0x14
  u32 ccr;

  // Offset: 0x1C
  u32 shrp2;

  // Offset: 0x20
  struct {
    u32 _reserved:16;
    u32 pendsv:8;
    u32 systick:8;
  } priority3;
};

}
}
