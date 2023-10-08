#pragma once

#include "hal/arm/registers.h"

void spi1_send(
  const u8* data,
  u16 len) {
	// When sending 8-bit frames, only the LSB 8 bits are used (mcu.reference 31.7.4).
	DMA->channel3.peripheral_address = ((u32) &SPI1->data) + 1;

	// We can't set memory values after DMA enablement.
	DMA->channel3.count = len;
	DMA->channel3.memory_address = (u32) data;

	// Enable DMA tx stream.
	DMA->channel3.config.priority = 2;
	DMA->channel3.config.enable_memory_increment = 1;
	DMA->channel3.config.memory_size = 0; // 8 bits.
	DMA->channel3.config.enable_circulator = 0;
	DMA->selection.channel3 = 1;
	DMA->channel3.config.transfer_direction = 1; // From memory to peripheral.
	DMA->channel3.config.enable = 1;
	DMA->channel3.config.peripheral_size = 0; // 8 bits.

	// Enable DMA for SPI1 tx.
	SPI1->control2.enable_transmit_dma = 1;
	// */

	// Other SPI1 configurations.
	SPI1->control1.is_master = 1;
	SPI1->control1.enable_bidi = 1;
	SPI1->control1.baud_rate = 2;
	SPI1->control1.bidi_enable_output = 1;
	SPI1->control1.first_data_clock_phase = 1;
	SPI1->control1.idle_clock_polarity = 1;
	SPI1->control1.data_frame_size = 0; // 8 bits.
	SPI1->control2.enable_ss_output = 1;

	SPI1->control1.enable = 1;

	// Wait for this command to be sent: wait for TXE = 1, then BSY = 0.
	while (!SPI1->status.tx_empty);
	while (SPI1->status.busy);

	if (DMA->channel3.count || DMA->status.transfer_error3) {
		DMA->channel3.count = 0;
	}

	DMA->channel3.config.enable = 0;
	SPI1->control1.enable = 0;
}
