#pragma once

#include "gfx/font.hh"
#include "gfx/fonts.hh"
#include "hal/arm/gpio.h"
#include "hal/arm/registers.h"
#include "hal/arm/stm32l0538.h"
#include "std/assert.hh"

namespace mcu = hal::arm::stm32l0538;

template <typename DMAChannelError>
inline void spi_send(
	DMAChannelError channel_error,
	volatile struct dma_channel* channel,
	volatile struct spi* spi,
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
	mcu::DMA->selection.channel3 = DMA_CHANNEL_SELECTION_1;
	
	spi_send(
		[] {return (bool) mcu::DMA->status.transfer_error3;},
		&mcu::DMA->channel3,
		mcu::SPI1,
		data,
		len);
}

inline void spi2_send(
	const u8* data,
	u16 len) {
	// Select the SPI2 functionality on DMA channel 7.
	mcu::DMA->selection.channel7 = DMA_CHANNEL_SELECTION_2;
	
	spi_send(
		[] {return (bool) mcu::DMA->status.transfer_error7;},
		&mcu::DMA->channel7,
		mcu::SPI2,
		data,
		len);
}

struct OLEDHAL {
	void init() {
		// For the Inland OLED SPI (128 x 64 pixels):
		// SPI2_NSS/CS: PB12
		// DC: PB7
		// SPI2_SCK: PB13
		// SPI2_MOSI: PB15
		// RES: PB14

		mcu::GPIO_B->mode.pin12 = GPIO_MODE_ALTERNATE; // OLED CS

		mcu::GPIO_B->mode.pin7 = GPIO_MODE_OUTPUT; // OLED D/C
		mcu::GPIO_B->output_speed.pin7 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_B->mode.pin13 = GPIO_MODE_ALTERNATE; // OLED SCK
		mcu::GPIO_B->pull.pin13 = 1;
		mcu::GPIO_B->output_speed.pin13 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_B->mode.pin15 = GPIO_MODE_ALTERNATE; // OLED MOSI
		mcu::GPIO_B->pull.pin15 = 2;
		mcu::GPIO_B->output_speed.pin15 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_B->mode.pin14 = GPIO_MODE_OUTPUT; // OLED Reset
		mcu::GPIO_B->output_speed.pin14 = GPIO_OUTPUTSPEED_VERYHIGH;
		
		mcu::GPIO_B->reset14 = 1;

		mcu::GPIO_B->set14 = 1;
	}

	void set_command() {
		// D/C low.
		mcu::GPIO_B->reset7 = 1;
	}

	void set_data() {
		// D/C high.
		mcu::GPIO_B->set7 = 1;
	}

	void send(
		const u8* data,
		const u16 len) {
		spi2_send(data, len);
	}
};

struct EPDHAL {
	void init() {
		// EPD (172 x 72 pixels):
		//   PB10 -> EPD Power
		//   PA8 -> EPD Busy
		//   PB2 -> EPD Reset
		//   PB11 -> EPD D/C (Data high)
		//   PA15 -> EPD CS
		//	   AF0 = SPI1_NSS?
		//   PB3 -> EPD SCK
		//     AF0 = SPI1_SCK
		//   PB5 -> EPD SDIN
		//     AF0 = SPI1_MOSI
		// Communicating would be (ref epd.specification pg 40):
		//   1. On the same cycle, hold CS low, set D/C appropriately
		//      (can't use automatic NSS management (mcu.reference 31.3.5)
		//       because we need to only drive it low when there's data)
		//      (or we can use it as long as we only enable the SPI peripheral
		//       when transmitting data, or hold clock low when not transmitting)
		//   2. Set SDIN for bit value per cycle
		// Could set DMA channel 3 to SPI1_TX (mcu.reference 11.4.7):
		//   1. Set peripheral register address.
		//   2. Set memory address to data to be written.
		//   3. Configure the total amount of data to be transferred.
		//   4. Configure transfer priority.
		//   5. Configure memory increment mode, memory data size, circular mode.
		//   6. Activate DMA channel 3.
		// To enable SPI for DMA:
		//   1. Enable DMA rx in SPI_CR2, if receiving.
		//   2. Enable DMA streams for tx and rx in DMA.
		//   3. Enable DMA tx in SPI_CR2, if transmitting.
		//   4. Enable SPI.

		// Configure appropriate GPIO ports for AF0.
		mcu::GPIO_A->mode.pin15 = GPIO_MODE_ALTERNATE; // EPD CS

		mcu::GPIO_B->mode.pin11 = GPIO_MODE_OUTPUT; // EPD D/C
		mcu::GPIO_B->output_speed.pin11 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_B->mode.pin3 = GPIO_MODE_ALTERNATE; // EPD SCK
		mcu::GPIO_B->pull.pin3 = 1;
		mcu::GPIO_B->output_speed.pin3 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_B->mode.pin5 = GPIO_MODE_ALTERNATE; // EPD SDIN
		mcu::GPIO_B->pull.pin5 = 2;
		mcu::GPIO_B->output_speed.pin5 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_A->mode.pin8 = GPIO_MODE_INPUT; // EPD Busy
		mcu::GPIO_A->pull.pin8 = 2;

		mcu::GPIO_B->mode.pin10 = GPIO_MODE_OUTPUT; // EPD Power
		mcu::GPIO_B->output_speed.pin10 = GPIO_OUTPUTSPEED_VERYHIGH;

		mcu::GPIO_B->mode.pin2 = GPIO_MODE_OUTPUT; // EPD Reset
		mcu::GPIO_B->output_speed.pin2 = GPIO_OUTPUTSPEED_VERYHIGH;

		// Enable EPD power, and send a reset.
		mcu::GPIO_B->reset10 = 1;
		mcu::GPIO_B->set2 = 1;
	}

	void set_data() {
			// Data: D/C high.
		mcu::GPIO_B->set11 = 1;
	}

	void set_command() {
		// Command: D/C low.
		mcu::GPIO_B->reset11 = 1;
	}

	void send(
		const u8* data,
		const u16 len) {
		spi1_send(data, len);
	}

	void wait() {
		while (mcu::GPIO_A->input.pin8);
	}
};

struct CRTHAL {
	int print_u8(u8 x) {
		while (!mcu::USART1->status.transmit_empty);

		mcu::USART1->transmit = x;
		
		return 0;
	}

	int print_string(const char* s) {
		while (*s) {
			while (!mcu::USART1->status.transmit_empty);

			mcu::USART1->transmit = (u8) *s;
			++s;
		}

		return 0;
	}
};
