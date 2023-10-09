#pragma once

#include "hal/arm/registers.h"
#include "hal/arm/stm32l0538.h"

inline void spi1_send(
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
		GPIO_A->mode.pin15 = GPIO_MODE_ALTERNATE; // EPD CS

		GPIO_A->mode.pin8 = GPIO_MODE_INPUT; // EPD Busy
		GPIO_A->pull.pin8 = 2;

		GPIO_B->mode.pin11 = GPIO_MODE_OUTPUT; // EPD D/C
		GPIO_B->output_speed.pin11 = 3;

		GPIO_B->mode.pin10 = GPIO_MODE_OUTPUT; // EPD Power
		GPIO_B->output_speed.pin10 = 3;

		GPIO_B->mode.pin3 = GPIO_MODE_ALTERNATE; // EPD SCK
		GPIO_B->pull.pin3 = 1;
		GPIO_B->output_speed.pin3 = 3;

		GPIO_B->mode.pin5 = GPIO_MODE_ALTERNATE; // EPD SDIN
		GPIO_B->pull.pin5 = 2;
		GPIO_B->output_speed.pin5 = 3;

		GPIO_B->mode.pin2 = GPIO_MODE_OUTPUT; // EPD Reset
		GPIO_B->output_speed.pin2 = 3;

		// Enable EPD power, and send a reset.
		GPIO_B->reset10 = 1;
		GPIO_B->set2 = 1;
	}

	void set_data() {
			// Data: D/C high.
		GPIO_B->set11 = 1;
	}

	void set_command() {
		// Command: D/C low.
		GPIO_B->reset11 = 1;
	}

	void send(
		const u8* data,
		const u16 len) {
		spi1_send(data, len);
	}

	void wait() {
		while (GPIO_A->input.pin8);
	}
};

struct CRTHAL {
	int print_u8(u8 x) {
		while (!USART1->status.transmit_empty);

		USART1->transmit = x;
		
		return 0;
	}

	int print_string(const char* s) {
		while (*s) {
			while (!USART1->status.transmit_empty);

			USART1->transmit = (u8) *s;
			++s;
		}

		return 0;
	}
};
