#pragma once

#include "types.h"

struct ahb {
	u32 dma:1;
	u32 padding:31;
};

struct apb1 {
	u32 _padding3:4;
	u32 timer6:1;
	u32 timer7:1;
	u32 _padding2:2;
	u32 _padding:24;
};

struct apb2 {
	u32 _padding:12;
	u32 spi1:1;
	u32 _padding2:1;
	u32 usart1:1;
	u32 _padding3:17;
};

#include "dma.h"
#include "exti.h"
#include "gpio.h"
#include "mpu.h"
#include "nvic.h"
#include "pwr.h"
#include "scb.h"
#include "spi.h"
#include "rcc.h"
#include "rtc.h"
#include "timer6.h"
#include "usart.h"
