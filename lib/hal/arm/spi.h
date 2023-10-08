#pragma once

#include "types.h"

struct spi {
	struct {
		u16 first_data_clock_phase:1;
		u16 idle_clock_polarity:1;
		u16 is_master:1;
		u16 baud_rate:3;
		u16 enable:1;
		u16 endianness:1;
		u16 internal_slave_select:1;
		u16 enable_software_slave:1;
		u16 enable_receive_only:1;
		u16 data_frame_size:1;
		u16 crc_next:1;
		u16 enable_hardware_crc:1;
		u16 bidi_enable_output:1;
		u16 enable_bidi:1;
	} control1;

	u8 _padding[0x02];

	// Offset: 0x04
	struct {
		u16 enable_receive_dma:1;
		u16 enable_transmit_dma:1;
		u16 enable_ss_output:1;
		u16 _reserved1:1;
		u16 frame_format:1;
		u16 enable_error_interrupt:1;
		u16 enable_rx_interrupt:1;
		u16 enable_tx_interrupt:1;
		u16 _reserved2:8;
	} control2;

	u8 _padding2[0x02];

	// Offset: 0x08
	struct {
		u16 rx_available:1;
		u16 tx_empty:1;
		u16 channel:1;
		u16 underrun:1;
		u16 crc_error:1;
		u16 mode_fault:1;
		u16 overrun:1;
		u16 busy:1;
		u16 frame_error:1;
		u16 _reserved:7;
	} status;

	u8 _padding3[0x02];

	// Offset: 0x0C
	u16 data;
};
