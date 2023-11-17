#pragma once

#include "types.hh"

namespace mcu {
namespace arm {

// Registers have to be written by u16s or u32s.
struct TIMERX {
	// Offset: 0x00
	struct {
		u16 enable_counter:1;
		u16 disable_update:1;
		u16 update_request_source:1;
		u16 one_pulse_mode:1;
		u16 _reserved2:3;
		u16 enable_auto_reload_preload:1;
		u16 _reserved:8;
	} control1;

	u8 _padding1[2];

	// Offset: 0x04
	struct {
		u16 _reserved2:4;
		u16 master_mode_selection:3;
		u16 _reserved:9;
	} control2;

	u8 _padding2[0x24 - 0x6];

	// Offset: 0x24
	u16 counter;

	u8 _padding3[2];

	// Offset: 0x28
	u16 prescaler;
};

}
}
