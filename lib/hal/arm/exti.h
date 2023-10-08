#pragma once

#include "types.h"

struct exti {
	// Offset: 0x00
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
	} interrupt,

		// Offset: 0x04
		event,

		// Offset: 0x08
		rising,

		// Offset: 0x0C
		falling,

		// Offset: 0x10
		software,

		// Offset: 0x14;
		pending;
};
