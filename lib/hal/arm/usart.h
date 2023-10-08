#pragma once

#include "types.h"

struct usart {
  // Offset: 0x00
  struct {
    u32 enabled:1;
    u32 _reserved1:2;
    u32 transmit_enabled:1;
    u32 _reserved2:9;
    u32 mute_enabled:1;
    u32 _reserved3:17;
  } control1;

  // Offset: 0x04
  struct {
    u32 _reserved1:11;
    u32 clock_enabled:1;
    u32 _reserved2:20;
  } control2;

  // Offset: 0x08
  u32 cr3;

  // Offset: 0x0C
  struct {
    u32 rate:16;
    u32 _reserved:16;
  } baud_rate;

  // Offset: 0x10
  u32 gtpr;

  // Offset: 0x14
  u32 rtor;

  // Offset: 0x18
  u32 rqr;

  // Offset: 0x1C
  struct {
    u32 parity_error:1;
    u32 framing_error:1;
    u32 noise_detected:1;
    u32 overrun_error:1;
    u32 idle_line_detected:1;
    u32 read_available:1;
    u32 transmit_complete:1;
    u32 transmit_empty:1;
    u32 _reserved:24;
  } status;

  // Offset: 0x20
  u32 icr;

  // Offset: 0x24
  u32 rdr;

  // Offset: 0x28
  struct {
    u32 transmit:8;
    u32 _reserved:24;
  };
};
