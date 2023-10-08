#pragma once

#include "types.h"

struct dma {
	struct {
		u32 global_interrupt1:1;
		u32 transfer_complete1:1;
		u32 transfer_half_complete1:1;
		u32 transfer_error1:1;
		u32 global_interrupt2:1;
		u32 transfer_complete2:1;
		u32 transfer_half_complete2:1;
		u32 transfer_error2:1;
		u32 global_interrupt3:1;
		u32 transfer_complete3:1;
		u32 transfer_half_complete3:1;
		u32 transfer_error3:1;
		u32 global_interrupt4:1;
		u32 transfer_complete4:1;
		u32 transfer_half_complete4:1;
		u32 transfer_error4:1;
		u32 global_interrupt5:1;
		u32 transfer_complete5:1;
		u32 transfer_half_complete5:1;
		u32 transfer_error5:1;
		u32 global_interrupt6:1;
		u32 transfer_complete6:1;
		u32 transfer_half_complete6:1;
		u32 transfer_error6:1;
		u32 global_interrupt7:1;
		u32 transfer_complete7:1;
		u32 transfer_half_complete7:1;
		u32 transfer_error7:1;
	} status;

	u8 _padding[0x04];

	// Offset: 0x08
	struct {
		struct {
			u32 enable:1;
			u32 enable_transfer_complete_interrupt:1;
			u32 enable_half_transfer_interrupt:1;
			u32 enable_transfer_error_interrupt:1;
			u32 transfer_direction:1;
			u32 enable_circulator:1;
			u32 enable_peripheral_increment:1;
			u32 enable_memory_increment:1;
			u32 peripheral_size:2;
			u32 memory_size:2;
			u32 priority:2;
			u32 enable_memory_to_memory:1;
			u32 _reserved:17;
		} config;

		// Offset: 0x04
		struct {
			u32 count:16;
			u32 _reserved:16;
		};

		// Offset: 0x08
		u32 peripheral_address;

		// Offset: 0x0C
		u32 memory_address;

		u32 _reserved2;
	} channel1, channel2, channel3, channel4,
	  channel5, channel6, channel7;

	u8 _reserved[0xA8 - 0x94];

	// Offset: 0xA8
	struct {
		u32 channel1:4;
		u32 channel2:4;
		u32 channel3:4;
		u32 channel4:4;
		u32 channel5:4;
		u32 channel6:4;
		u32 channel7:4;
		u32 _reserved:4;
	} selection;
};
