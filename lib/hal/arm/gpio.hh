#pragma once

#include "types.hh"

namespace hal {
namespace arm {

struct GPIO {
	enum struct Mode: u32 {
		INPUT = 0b00,
		OUTPUT = 0b01,
		ALTERNATE = 0b10,
		ANALOG = 0b11,
	};

	enum struct OutputType: u32 {
		PUSHPULL = 0b0,
		OPENDRAIN = 0b1,
	};

	enum struct OutputSpeed: u32 {
		LOW = 0b00,
		MEDIUM = 0b01,
		HIGH = 0b10,
		VERYHIGH = 0b11,
	};

	// Offset: 0x00
	struct {
		Mode pin0:2;
		Mode pin1:2;
		Mode pin2:2;
		Mode pin3:2;
		Mode pin4:2;
		Mode pin5:2;
		Mode pin6:2;
		Mode pin7:2;
		Mode pin8:2;
		Mode pin9:2;
		Mode pin10:2;
		Mode pin11:2;
		Mode pin12:2;
		Mode pin13:2;
		Mode pin14:2;
		Mode pin15:2;
	} mode;

	// Offset: 0x04
	struct {
		OutputType pin0:1;
		OutputType pin1:1;
		OutputType pin2:1;
		OutputType pin3:1;
		OutputType pin4:1;
		OutputType pin5:1;
		OutputType pin6:1;
		OutputType pin7:1;
		OutputType pin8:1;
		OutputType pin9:1;
		OutputType pin10:1;
		OutputType pin11:1;
		OutputType pin12:1;
		OutputType pin13:1;
		OutputType pin14:1;
		OutputType pin15:1;
		OutputType _reserved:16;
	} output_type;

	// Offset: 0x08
	struct {
		OutputSpeed pin0:2;
		OutputSpeed pin1:2;
		OutputSpeed pin2:2;
		OutputSpeed pin3:2;
		OutputSpeed pin4:2;
		OutputSpeed pin5:2;
		OutputSpeed pin6:2;
		OutputSpeed pin7:2;
		OutputSpeed pin8:2;
		OutputSpeed pin9:2;
		OutputSpeed pin10:2;
		OutputSpeed pin11:2;
		OutputSpeed pin12:2;
		OutputSpeed pin13:2;
		OutputSpeed pin14:2;
		OutputSpeed pin15:2;
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

}
}
