#include "hal/arm/registers.h"

#include "types.h"
#include "stm32l0538.h"

#define MCU_DEFINE_REGISTER(address, name, type) volatile type* const name = (volatile type* const) address

MCU_DEFINE_REGISTER(0x40001000, TIMER6, struct timerx);
MCU_DEFINE_REGISTER(0x40007000, PWR_CR, struct pwr_cr);
MCU_DEFINE_REGISTER(0x40010400, EXTI, struct exti);
MCU_DEFINE_REGISTER(0x40013000, SPI1, struct spi);
MCU_DEFINE_REGISTER(0x40013800, USART1, struct usart);
MCU_DEFINE_REGISTER(0x40015808, DBG_APB1_FREEZE, struct apb1);
MCU_DEFINE_REGISTER(0x40021000, RCC, struct rcc);
MCU_DEFINE_REGISTER(0x40020000, DMA, struct dma);
MCU_DEFINE_REGISTER(0x50000000, GPIO_A, struct gpio);
MCU_DEFINE_REGISTER(0x50000400, GPIO_B, struct gpio);
MCU_DEFINE_REGISTER(0xE000E100, NVIC, struct nvic);
MCU_DEFINE_REGISTER(0xE000E100, MPU, struct mpu);
MCU_DEFINE_REGISTER(0xE000ED00, SCB, struct scb);
