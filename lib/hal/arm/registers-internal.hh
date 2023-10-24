#pragma once

#include "types.hh"

namespace hal {
namespace arm {

struct AHB {
	u32 dma:1;
	u32 dma2:1;
	u32 padding:30;
};

struct APB1 {
	u32 _padding3:4;
	u32 timer6:1;
	u32 timer7:1;
	u32 _padding2:8;
	u32 spi2:1;
	u32 _padding:17;
};

struct APB2 {
	u32 _padding:12;
	u32 spi1:1;
	u32 _padding2:1;
	u32 usart1:1;
	u32 _padding3:17;
};

#define MCU_DECLARE_REGISTER(name, type) extern volatile type* const name

#define MCU_DEFINE_REGISTER(address, name, type) volatile type* const name = (volatile type* const) address

}
}
