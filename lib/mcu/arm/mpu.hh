#pragma once

#include "types.hh"

namespace mcu {
namespace arm {

struct MPU {
  // Offset: 0x00
  struct {
    u32 separate:1;
    u32 _reserved1:7;
    u32 data_region_count:8;
    u32 instruction_region_count:8;
    u32 _reserved2:8;
  } type;

  // Offset: 0x04
  struct {
    u32 enable:1;
    u32 enable_during_interrupts:1;
    u32 enable_privigiled_access_to_default_map:1;
    u32 _reserved:29;
  } control;

  // Offset: 0x08
  struct {
    u32 number:8;
    u32 _reserved:24;
  } region;

  // Offset: 0x0C
  struct {
    u32 region:4;
    u32 region_is_valid:1;
    u32 base:27;
  } address;

  // Offset: 0x10
  struct {
    u32 enable:1;
    u32 size:5;
    u32 _reserved1:2;
    u32 subregion_disable:8;
    u32 bufferable:1;
    u32 cacheable:1;
    u32 shareable:1;
    u32 _reserved2:5;
    u32 access_permission:3;
    u32 _reserved3:1;
    u32 disable_instruction_fetch:1;
    u32 _reserved4:3;
  } attributes;
};

}
}
