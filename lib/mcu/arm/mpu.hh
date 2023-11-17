#pragma once

#include "types.hh"

namespace mcu {
namespace arm {

struct MPU {
  // Offset: 0x00
  struct {
    u8 separate:1;
    u8 _reserved1:7;
    u8 data_region_count:8;
    u8 instruction_region_count:8;
    u8 _reserved2:8;
  } type;

  // Offset: 0x04
  struct {
    u8 enable:1;
    u8 enable_during_interrupts:1;
    u8 enable_privigiled_access_to_default_map:1;
    u32 _reserved:29;
  } control;

  // Offset: 0x08
  struct {
    u8 number:8;
    u32 _reserved:24;
  } region;

  // Offset: 0x0C
  struct {
    u8 region:4;
    u8 valid:1;
    u32 base:27;
  } address;

  // Offset: 0x10
  struct {
    u8 enable:1;
    u8 size:5;
    u8 _reserved1:2;
    u8 subregion_disable:8;
    u8 bufferable:1;
    u8 cacheable:1;
    u8 shareable:1;
    u8 _reserved2:5;
    u8 access_permission:3;
    u8 _reserved3:1;
    u8 disable_instruction_fetch:1;
    u8 _reserved4:3;
  } attributes;
};

}
}
