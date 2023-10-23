#pragma once

#include "registers.h"
#include "registers-internal.h"

namespace hal {
namespace arm {
namespace stm32f051r8 {

MCU_DECLARE_REGISTER(RCC, struct rcc);
MCU_DECLARE_REGISTER(GPIO_A, struct gpio);
MCU_DECLARE_REGISTER(GPIO_B, struct gpio);
MCU_DECLARE_REGISTER(GPIO_C, struct gpio);
MCU_DECLARE_REGISTER(GPIO_D, struct gpio);
MCU_DECLARE_REGISTER(GPIO_E, struct gpio);
MCU_DECLARE_REGISTER(GPIO_F, struct gpio);

}
}
}
