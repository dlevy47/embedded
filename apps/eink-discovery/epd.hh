#pragma once

#include "app.hh"
#include "picture.hh"
#include "spi.hh"

#include "devices/epd/epd.hh"

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
		mcu::GPIO_A->mode.pin15 = hal::arm::GPIO::Mode::ALTERNATE; // EPD CS

		mcu::GPIO_B->mode.pin11 = hal::arm::GPIO::Mode::OUTPUT; // EPD D/C
		mcu::GPIO_B->output_speed.pin11 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_B->mode.pin3 = hal::arm::GPIO::Mode::ALTERNATE; // EPD SCK
		mcu::GPIO_B->pull.pin3 = 1;
		mcu::GPIO_B->output_speed.pin3 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_B->mode.pin5 = hal::arm::GPIO::Mode::ALTERNATE; // EPD SDIN
		mcu::GPIO_B->pull.pin5 = 2;
		mcu::GPIO_B->output_speed.pin5 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_A->mode.pin8 = hal::arm::GPIO::Mode::INPUT; // EPD Busy
		mcu::GPIO_A->pull.pin8 = 2;

		mcu::GPIO_B->mode.pin10 = hal::arm::GPIO::Mode::OUTPUT; // EPD Power
		mcu::GPIO_B->output_speed.pin10 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_B->mode.pin2 = hal::arm::GPIO::Mode::OUTPUT; // EPD Reset
		mcu::GPIO_B->output_speed.pin2 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

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

	bool is_busy() {
		return mcu::GPIO_A->input.pin8 == 1;
	}
};

inline Error epd_test(Scheduler* scheduler) {
	_crt.print("running epd test\r\n");
	
	devices::epd::EPD<EPDHAL> epd;
	epd.init();

	epd.draw_xbm1pp(
		picture_1,
		sizeof(picture_1) / sizeof(*picture_1));

	epd.refresh();

	while (epd.is_busy()) {
		scheduler->yield();
	}
	
	_crt.print("epd test done\r\n");
	
	return Error{};
}
