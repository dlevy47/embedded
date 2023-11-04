#pragma once

#include "app.hh"
#include "spi.hh"

#include "devices/oled/sh1106.hh"
#include "gfx/fonts.hh"

struct OLEDHAL {
	void init() {
		// For the Inland OLED SPI (128 x 64 pixels):
		// SPI2_NSS/CS: PB12
		// DC: PB7
		// SPI2_SCK: PB13
		// SPI2_MOSI: PB15
		// RES: PB14

		mcu::GPIO_B->mode.pin12 = hal::arm::GPIO::Mode::ALTERNATE; // OLED CS

		mcu::GPIO_B->mode.pin7 = hal::arm::GPIO::Mode::OUTPUT; // OLED D/C
		mcu::GPIO_B->output_speed.pin7 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_B->mode.pin13 = hal::arm::GPIO::Mode::ALTERNATE; // OLED SCK
		mcu::GPIO_B->pull.pin13 = 1;
		mcu::GPIO_B->output_speed.pin13 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_B->mode.pin15 = hal::arm::GPIO::Mode::ALTERNATE; // OLED MOSI
		mcu::GPIO_B->pull.pin15 = 2;
		mcu::GPIO_B->output_speed.pin15 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

		mcu::GPIO_B->mode.pin14 = hal::arm::GPIO::Mode::OUTPUT; // OLED Reset
		mcu::GPIO_B->output_speed.pin14 = hal::arm::GPIO::OutputSpeed::VERYHIGH;
		
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

inline Error blink(Scheduler* scheduler) {
	_crt.print("running oled test\r\n");
	typedef devices::oled::SH1106<OLEDHAL, 128, 64> OLED;
	OLED oled;
	oled.init();
	oled.clear();

	const gfx::Font* font = &gfx::fonts::Misaki;

	// All the Misaki glyphs are at -1 y offset, so move base up 1 to
	// compensate.
	i32 base = font->point_size - 1 - 1;
	oled.draw_text(0, base, font, "こんにちは大野夏実様");
	base += font->point_size;
	oled.draw_text(0, base, font, "Hello world!");
	
	oled.show();
	_crt.print("oled test done\r\n");
	
	mcu::NVIC->setenable.line5 = 1;
	for (size_t i = 0; i < 60; ++i) {
		if ((mcu::TIMER6->counter / 1024) % 2) {
			mcu::GPIO_A->set5 = 1;

			for (u32 i = 0; i < 10000; ++i);

			mcu::GPIO_A->reset5 = 1;
			oled.send_command(static_cast<u8>(OLED::Command::DISPLAYREVERSE));
		} else {
			mcu::GPIO_B->set4 = 1;

			for (u32 i = 0; i < 10000; ++i);

			mcu::GPIO_B->reset4 = 1;
			oled.send_command(static_cast<u8>(OLED::Command::DISPLAYNORMAL));
		}

		for (u32 i = 0; i < 10001; ++i);

		scheduler->yield();
	}
	
	return Error{};
}
