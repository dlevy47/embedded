#pragma once

#include "registers-internal.hh"
#include "types.hh"

namespace mcu {
namespace arm {

struct RCC {
	struct GPIO {
		u8 a:1;
		u8 b:1;
		u8 c:1;
		u8 d:1;
		u8 e:1;
		u8 f:1;
		u8 g:1;
		u8 h:1;
		u32 _padding:24;
	};
	
	u8 _padding0[0x04];

	// Offset: 0x04
	struct {
		u32 hsi16_calibration:8;
		u32 hsi16_trim:5;
		u32 msi_range:3;
		u32 msi_calibration:8;
		u32 msi_trim:8;
	} clock_calibration;

	u8 _padding1[0x04];

	// Offset: 0x0C
	struct {
		u32 clock_switch:2;
		u32 clock_switch_status:2;
		u32 ahb_prescale:4;
		u32 apb1_prescale:3;
		u32 apb2_prescale:3;
		u32 padding:18;
	} clock_configuration;

	u8 _padding2[0x0C];

	// Offset: 0x1C
	GPIO gpio_reset;

	u8 _padding3[0x0C];

	// Offset: 0x2C
	GPIO gpio_enable;

	// Offset: 0x30
	AHB ahb_enable;

	// Offset: 0x34
	APB2 apb2_enable;

	// Offset: 0x38
	APB1 apb1_enable;

	// Offset: 0x3C
	GPIO gpio_enable_sleep;
};

}
}
