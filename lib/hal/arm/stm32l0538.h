#pragma once

#include "registers.h"
#include "registers-internal.h"

MCU_DECLARE_REGISTER(TIMER6, struct timerx);
MCU_DECLARE_REGISTER(PWR_CR, struct pwr_cr);
MCU_DECLARE_REGISTER(EXTI, struct exti);
MCU_DECLARE_REGISTER(SPI1, struct spi);
MCU_DECLARE_REGISTER(USART1, struct usart);
MCU_DECLARE_REGISTER(DBG_APB1_FREEZE, struct apb1);
MCU_DECLARE_REGISTER(RCC, struct rcc);
MCU_DECLARE_REGISTER(DMA, struct dma);
MCU_DECLARE_REGISTER(GPIO_A, struct gpio);
MCU_DECLARE_REGISTER(GPIO_B, struct gpio);
MCU_DECLARE_REGISTER(NVIC, struct nvic);
MCU_DECLARE_REGISTER(MPU, struct mpu);
MCU_DECLARE_REGISTER(SCP, struct scb);
