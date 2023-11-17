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

		MCU::GPIO_B->mode.pin12 = mcu::arm::GPIO::Mode::ALTERNATE; // OLED CS

		MCU::GPIO_B->mode.pin7 = mcu::arm::GPIO::Mode::OUTPUT; // OLED D/C
		MCU::GPIO_B->output_speed.pin7 = mcu::arm::GPIO::OutputSpeed::VERYHIGH;

		MCU::GPIO_B->mode.pin13 = mcu::arm::GPIO::Mode::ALTERNATE; // OLED SCK
		MCU::GPIO_B->pull.pin13 = 1;
		MCU::GPIO_B->output_speed.pin13 = mcu::arm::GPIO::OutputSpeed::VERYHIGH;

		MCU::GPIO_B->mode.pin15 = mcu::arm::GPIO::Mode::ALTERNATE; // OLED MOSI
		MCU::GPIO_B->pull.pin15 = 2;
		MCU::GPIO_B->output_speed.pin15 = mcu::arm::GPIO::OutputSpeed::VERYHIGH;

		MCU::GPIO_B->mode.pin14 = mcu::arm::GPIO::Mode::OUTPUT; // OLED Reset
		MCU::GPIO_B->output_speed.pin14 = mcu::arm::GPIO::OutputSpeed::VERYHIGH;
		
		MCU::GPIO_B->reset14 = 1;

		MCU::GPIO_B->set14 = 1;
	}

	void set_command() {
		// D/C low.
		MCU::GPIO_B->reset7 = 1;
	}

	void set_data() {
		// D/C high.
		MCU::GPIO_B->set7 = 1;
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
	
	MCU::NVIC->setenable.line5 = 1;
	for (size_t i = 0; i < 60; ++i) {
		if ((MCU::TIMER6->counter / 1024) % 2) {
			MCU::GPIO_A->set5 = 1;

			for (u32 i = 0; i < 10000; ++i);

			MCU::GPIO_A->reset5 = 1;
			oled.send_command(static_cast<u8>(OLED::Command::DISPLAYREVERSE));
			_crt.print("display reverse\r\n");
		} else {
			MCU::GPIO_B->set4 = 1;

			for (u32 i = 0; i < 10000; ++i);

			MCU::GPIO_B->reset4 = 1;
			oled.send_command(static_cast<u8>(OLED::Command::DISPLAYNORMAL));
			_crt.print("display normal\r\n");
		}

		for (u32 i = 0; i < 10001; ++i);

		scheduler->yield();
	}
	
	_crt.print("oled test done\r\n");
	
	return Error{};
}
