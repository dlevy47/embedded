#pragma once

#include "app.hh"

template <typename DMAChannelError>
inline void spi_send(
	DMAChannelError channel_error,
	volatile mcu::arm::DMA::Channel* channel,
	volatile mcu::arm::SPI* spi,
	const u8* data,
	u16 len) {
	// Non-DMA path:
	// spi->control1.is_master = 1;
	// spi->control1.enable_bidi = 1;
	// spi->control1.baud_rate = 2;
	// spi->control1.bidi_enable_output = 1;
	// spi->control1.first_data_clock_phase = 1;
	// spi->control1.idle_clock_polarity = 1;
	// spi->control1.data_frame_size = 0; // 8 bits.
	// spi->control2.enable_ss_output = 1;
	//
	// spi->control1.enable = 1;
	//
	// for (u16 c = 0; c < len; ++c) {
	// 	spi->data = data[c];
	//
	// 	while (!spi->status.tx_empty);
	// 	while (spi->status.busy);
	// }
	//
	// spi->control1.enable = 0;
	
	// DMA path:
	// When sending 8-bit frames, only the LSB 8 bits are used (mcu.reference 31.7.4).
	channel->peripheral_address = ((u32) &spi->data);// + 1;

	// We can't set memory values after DMA enablement.
	channel->count = len;
	channel->memory_address = (u32) data;

	// Enable DMA tx stream.
	channel->config.priority = 2;
	channel->config.enable_memory_increment = 1;
	channel->config.memory_size = 0; // 8 bits.
	channel->config.enable_circulator = 0;
	channel->config.transfer_direction = 1; // From memory to peripheral.
	channel->config.enable = 1;
	channel->config.peripheral_size = 0; // 8 bits.

	// Enable DMA for SPI tx.
	spi->control2.enable_transmit_dma = 1;

	// Other SPI configurations.
	spi->control1.is_master = 1;
	spi->control1.enable_bidi = 1;
	spi->control1.baud_rate = 2;
	spi->control1.bidi_enable_output = 1;
	spi->control1.first_data_clock_phase = 1;
	spi->control1.idle_clock_polarity = 1;
	spi->control1.data_frame_size = 0; // 8 bits.
	spi->control2.enable_ss_output = 1;

	spi->control1.enable = 1;

	// Wait for this command to be sent: wait for TXE = 1, then BSY = 0.
	while (!spi->status.tx_empty);
	while (spi->status.busy);

	if (channel->count || channel_error()) {
		channel->count = 0;
	}

	channel->config.enable = 0;
	spi->control1.enable = 0;
}

inline void spi1_send(
	const u8* data,
	u16 len) {
	// Select the SPI1 functionality on DMA channel 3.
	MCU::DMA->selection.channel3 = mcu::arm::DMA::Channel::Selection::SELECTION_1;
	
	spi_send(
		[] {return (bool) MCU::DMA->status.transfer_error3;},
		&MCU::DMA->channel3,
		MCU::SPI1,
		data,
		len);
}

inline void spi2_send(
	const u8* data,
	u16 len) {
	// Select the SPI2 functionality on DMA channel 7.
	MCU::DMA->selection.channel7 = mcu::arm::DMA::Channel::Selection::SELECTION_2;
	
	spi_send(
		[] {return (bool) MCU::DMA->status.transfer_error7;},
		&MCU::DMA->channel7,
		MCU::SPI2,
		data,
		len);
}
