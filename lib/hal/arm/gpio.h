#pragma once

#include "types.h"

enum gpio_mode: u32 {
	GPIO_MODE_INPUT = 0b00,
	GPIO_MODE_OUTPUT = 0b01,
	GPIO_MODE_ALTERNATE = 0b10,
	GPIO_MODE_ANALOG = 0b11,
};

enum gpio_outputtype: u32 {
	GPIO_OUTPUTTYPE_PUSHPULL = 0b0,
	GPIO_OUTPUTTYPE_OPENDRAIN = 0b1,
};

struct gpio {
	// Offset: 0x00
	struct {
		enum gpio_mode pin0:2;
		enum gpio_mode pin1:2;
		enum gpio_mode pin2:2;
		enum gpio_mode pin3:2;
		enum gpio_mode pin4:2;
		enum gpio_mode pin5:2;
		enum gpio_mode pin6:2;
		enum gpio_mode pin7:2;
		enum gpio_mode pin8:2;
		enum gpio_mode pin9:2;
		enum gpio_mode pin10:2;
		enum gpio_mode pin11:2;
		enum gpio_mode pin12:2;
		enum gpio_mode pin13:2;
		enum gpio_mode pin14:2;
		enum gpio_mode pin15:2;
	} mode;

	// Offset: 0x04
	struct {
		enum gpio_outputtype pin0:1;
		enum gpio_outputtype pin1:1;
		enum gpio_outputtype pin2:1;
		enum gpio_outputtype pin3:1;
		enum gpio_outputtype pin4:1;
		enum gpio_outputtype pin5:1;
		enum gpio_outputtype pin6:1;
		enum gpio_outputtype pin7:1;
		enum gpio_outputtype pin8:1;
		enum gpio_outputtype pin9:1;
		enum gpio_outputtype pin10:1;
		enum gpio_outputtype pin11:1;
		enum gpio_outputtype pin12:1;
		enum gpio_outputtype pin13:1;
		enum gpio_outputtype pin14:1;
		enum gpio_outputtype pin15:1;
		enum gpio_outputtype _reserved:16;
	} output_type;

	// Offset: 0x08
	struct {
		u32 pin0:2;
		u32 pin1:2;
		u32 pin2:2;
		u32 pin3:2;
		u32 pin4:2;
		u32 pin5:2;
		u32 pin6:2;
		u32 pin7:2;
		u32 pin8:2;
		u32 pin9:2;
		u32 pin10:2;
		u32 pin11:2;
		u32 pin12:2;
		u32 pin13:2;
		u32 pin14:2;
		u32 pin15:2;
	} output_speed;

	// Offset: 0x0C
	struct {
		u32 pin0:2;
		u32 pin1:2;
		u32 pin2:2;
		u32 pin3:2;
		u32 pin4:2;
		u32 pin5:2;
		u32 pin6:2;
		u32 pin7:2;
		u32 pin8:2;
		u32 pin9:2;
		u32 pin10:2;
		u32 pin11:2;
		u32 pin12:2;
		u32 pin13:2;
		u32 pin14:2;
		u32 pin15:2;
	} pull;

	// Offset: 0x10
	struct {
		u32 pin0:1;
		u32 pin1:1;
		u32 pin2:1;
		u32 pin3:1;
		u32 pin4:1;
		u32 pin5:1;
		u32 pin6:1;
		u32 pin7:1;
		u32 pin8:1;
		u32 pin9:1;
		u32 pin10:1;
		u32 pin11:1;
		u32 pin12:1;
		u32 pin13:1;
		u32 pin14:1;
		u32 pin15:1;
		u32 _reserved:16;
	} input;

	// Offset: 0x14
	struct {
		u32 pin0:1;
		u32 pin1:1;
		u32 pin2:1;
		u32 pin3:1;
		u32 pin4:1;
		u32 pin5:1;
		u32 pin6:1;
		u32 pin7:1;
		u32 pin8:1;
		u32 pin9:1;
		u32 pin10:1;
		u32 pin11:1;
		u32 pin12:1;
		u32 pin13:1;
		u32 pin14:1;
		u32 pin15:1;
		u32 _reserved:16;
	} output;

	// Offset: 0x18
	struct {
		u32 set0:1;
		u32 set1:1;
		u32 set2:1;
		u32 set3:1;
		u32 set4:1;
		u32 set5:1;
		u32 set6:1;
		u32 set7:1;
		u32 set8:1;
		u32 set9:1;
		u32 set10:1;
		u32 set11:1;
		u32 set12:1;
		u32 set13:1;
		u32 set14:1;
		u32 set15:1;
		u32 reset0:1;
		u32 reset1:1;
		u32 reset2:1;
		u32 reset3:1;
		u32 reset4:1;
		u32 reset5:1;
		u32 reset6:1;
		u32 reset7:1;
		u32 reset8:1;
		u32 reset9:1;
		u32 reset10:1;
		u32 reset11:1;
		u32 reset12:1;
		u32 reset13:1;
		u32 reset14:1;
		u32 reset15:1;
	};

	// Offset: 0x1C
	u32 lckr;

	// Offset: 0x20
	struct {
		u32 pin0:4;
		u32 pin1:4;
		u32 pin2:4;
		u32 pin3:4;
		u32 pin4:4;
		u32 pin5:4;
		u32 pin6:4;
		u32 pin7:4;
		u32 pin8:4;
		u32 pin9:4;
		u32 pin10:4;
		u32 pin11:4;
		u32 pin12:4;
		u32 pin13:4;
		u32 pin14:4;
		u32 pin15:4;
	} alternate;

	// Offset: 0x28
	u32 brr;
};
