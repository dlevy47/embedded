// parallel-flash-dumper dumps the contents of a NAND flash chip that uses a
// parallel interface. Namely, it has been written to support dumping the
// contents of the K9XXG08UXA line of Samsung flash chips.
//
// parallel-flash-dumper is written to run on an STM32F0 discovery board. The
// following pins are allocated:
//   PA1 - flash IO0
//   PA2 - mcu USART1 TX
//   PA3- flash IO1
//   PA4 - flash IO2
//   PA5 - flash IO3
//   PA6 - flash IO4
//   PA7 - flash IO5
//   PA8 - flash IO6
//   PA9 - flash IO7
//   PA10 - flash Command Latch Enable
//   PA11 - flash Address Latch Enable
//   PA12 - flash Read Enable
//   PA15 - flash Write Enable
//   PB0 - flash Busy
#include "hal/arm/stm32f051r8.hh"

extern "C" void _start() {
  // Enable peripheral clocks.
  RCC->gpio_enable.a = 1;
  RCC->gpio_enable.b = 1;
  RCC->gpio_enable.c = 1;
  RCC->gpio_enable.d = 1;
  RCC->gpio_enable.e = 1;
  RCC->gpio_enable.f = 1;
  RCC->ahb_enable.dma = 1;
  RCC->ahb_enable.dma2 = 1;
	RCC->apb2_enable.usart1 = 1;
}
