#pragma once

#include "registers.hh"
#include "registers-internal.hh"

namespace hal {
namespace arm {
namespace stm32f051r8 {

MCU_DECLARE_REGISTER(RCC, arm::RCC);
MCU_DECLARE_REGISTER(GPIO_A, arm::GPIO);
MCU_DECLARE_REGISTER(GPIO_B, arm::GPIO);
MCU_DECLARE_REGISTER(GPIO_C, arm::GPIO);
MCU_DECLARE_REGISTER(GPIO_D, arm::GPIO);
MCU_DECLARE_REGISTER(GPIO_E, arm::GPIO);
MCU_DECLARE_REGISTER(GPIO_F, arm::GPIO);

}
}
}
