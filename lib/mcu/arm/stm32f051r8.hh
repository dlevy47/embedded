#pragma once

#include "registers.hh"
#include "registers-internal.hh"

namespace mcu {
namespace arm {

struct STM32F051R8 {
  MCU_DEFINE_REGISTER(0x40021000, RCC, arm::RCC);
  MCU_DEFINE_REGISTER(0x48000000, GPIO_A, arm::GPIO);
  MCU_DEFINE_REGISTER(0x48000400, GPIO_B, arm::GPIO);
  MCU_DEFINE_REGISTER(0x48000800, GPIO_C, arm::GPIO);
  MCU_DEFINE_REGISTER(0x48000C00, GPIO_D, arm::GPIO);
  MCU_DEFINE_REGISTER(0x48001000, GPIO_E, arm::GPIO);
  MCU_DEFINE_REGISTER(0x48001400, GPIO_F, arm::GPIO);
};

}
}
