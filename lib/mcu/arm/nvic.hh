#pragma once

#include "types.hh"

namespace mcu {
namespace arm {

// Use u32 instead of u8, because cortex-m0 processors require nvic writes to be word aligned.
// Combined with the -fstrict-volatile-bitfields option to GCC (and volatile attributes on
// appropriate declarations), GCC will emit full length load and store instructions (i.e. str
// instead of strb).
struct NVIC {
	struct {
		u32 line0:1;
		u32 line1:1;
		u32 line2:1;
		u32 line3:1;
		u32 line4:1;
		u32 line5:1;
		u32 line6:1;
		u32 line7:1;
		u32 line8:1;
		u32 line9:1;
		u32 line10:1;
		u32 line11:1;
		u32 line12:1;
		u32 line13:1;
		u32 line14:1;
		u32 line15:1;
		u32 line16:1;
		u32 line17:1;
		u32 line18:1;
		u32 line19:1;
		u32 line20:1;
		u32 line21:1;
		u32 line22:1;
		u32 line23:1;
		u32 line24:1;
		u32 line25:1;
		u32 line26:1;
		u32 line27:1;
		u32 line28:1;
		u32 line29:1;
		u32 line30:1;
		u32 line31:1;
	} setenable,

	_padding0[0x1F],

	clearenable,

	_padding1[0x1F],

	setpending,

	_padding2[0x1F],

	clearpending;
};

}
}
