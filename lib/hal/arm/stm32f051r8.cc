#include "hal/arm/stm32f051r8.hh"

namespace hal {
namespace arm {
namespace stm32f051r8 {

MCU_DEFINE_REGISTER(0x40021000, RCC, struct rcc);
MCU_DEFINE_REGISTER(0x48000000, GPIO_A, struct gpio);
MCU_DEFINE_REGISTER(0x48000400, GPIO_B, struct gpio);
MCU_DEFINE_REGISTER(0x48000800, GPIO_C, struct gpio);
MCU_DEFINE_REGISTER(0x48000C00, GPIO_D, struct gpio);
MCU_DEFINE_REGISTER(0x48001000, GPIO_E, struct gpio);
MCU_DEFINE_REGISTER(0x48001400, GPIO_F, struct gpio);

}
}
}
