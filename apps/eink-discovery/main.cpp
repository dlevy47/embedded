#include "main.hh"
#include "crt.hh"
#include "types.h"

#include "crt.hh"
#include "devices/epd/epd.hh"
#include "hal/arm/stm32l0538.h"
#include "sys/isr.h"
#include "sys/init.h"
#include "sys/scheduler.h"

#include "picture.h"

u32 color = 0;

static void button_handler() {
	color = !color;

	EXTI->pending.line0 = 1;
}

// delay waits for the specified number of 1/1024s of a second to elapse.
static void delay(u32 mibis) {
	TIMER6->control1.one_pulse_mode = 1;
}

static void epd_test() {
	devices::EPD<EPDHAL> epd;
	epd.init();

	epd.draw_xbm1pp(
		picture_1,
		sizeof(picture_1) / sizeof(*picture_1));

	epd.refresh_and_wait();
}

extern "C" void _start() {
	sys_isr_uservector[5] = button_handler;

	// For UART, configure 115200 8N1:
	//   115200 baud rate
	//   8 bit data
	//   Odd parity
	//   1 stop bit

	// Enable interrupt handling for PA0 input.
	//   Reference 13.4: PA0 -> EXTI0
	//   Reference 12.3: EXTI0 and EXTI1 interrupts map to IRQ 5
	EXTI->interrupt.line0 = 1;
	EXTI->rising.line0 = 1;
	NVIC->setenable.line5 = 1;

	// Enable GPIOA and GPIOB clocks.
	RCC->gpio_enable.a = 1;
	RCC->gpio_enable.b = 1;

	// Enable SPI1, SPI2, and DMA clocks.
	RCC->apb1_enable.spi2 = 1;
	RCC->apb2_enable.spi1 = 1;
	RCC->ahb_enable.dma = 1;

	// Enable USART1 clock.
	RCC->apb2_enable.usart1 = 1;

	// Enable TIMER6 clock.
	RCC->apb1_enable.timer6 = 1;
	DBG_APB1_FREEZE->timer6 = 1;

	// Enable PA0 for input.
	GPIO_A->mode.pin0 = GPIO_MODE_INPUT;

	// Enable PA8, and PA9 for USART output.
	// NOTE: It's important to set the alternate function index first, because
	// otherwise the pin will have a short period when it is enabled, but not
	// connected to the USART, and spurious data will be sent.
	GPIO_A->alternate.pin8 = 4;
	GPIO_A->mode.pin8 = GPIO_MODE_ALTERNATE;
	GPIO_A->output_type.pin8 = GPIO_OUTPUTTYPE_PUSHPULL;
	GPIO_A->alternate.pin9 = 4;
	GPIO_A->mode.pin9 = GPIO_MODE_ALTERNATE;
	GPIO_A->output_type.pin9 = GPIO_OUTPUTTYPE_PUSHPULL;

	// Enable PA5 and PB4 for output.
	// On the dev board, these correspond to the red and green LEDs.
	GPIO_A->mode.pin5 = GPIO_MODE_OUTPUT;
	GPIO_B->mode.pin4 = GPIO_MODE_OUTPUT;
	
	GPIO_B->mode.pin6 = GPIO_MODE_OUTPUT;
	GPIO_B->output_speed.pin6 = GPIO_OUTPUTSPEED_VERYHIGH;

	// TIMER6 is an APB1 peripheral, and so uses the PCLK1 clock source.
	// The PCLK1 frequency is the prescaled HCLK frequency.
	// The HCLK frequency is the prescaled SYSCLK frequency.
	// The SYSCLK frequency is determined from RCC->clock_configuration.clock_switch_status.
	//   On reset, it is the MSICLK frequency.
	// The MSICLK frequency is determined from 32768 * (1 << RCC->clock_calibration.msi_range + 1).
	u32 msiclk = 32768 * (1 << (RCC->clock_calibration.msi_range + 1));
	// For now, elide the prescaling (because we know what our values are).
	u32 pclk1 = msiclk;

	// Enable TIMER6.
	TIMER6->control1.enable_counter = 1;
	TIMER6->prescaler = pclk1 / 1024;
	// After application of the prescaler, TIMER6's values should be 1/1024 of a second.

	// Configure USART1.
	if (USART1->control1.over8) {
		USART1->baud_rate.rate = 2 * msiclk / 115600;
	} else {
		USART1->baud_rate.rate = msiclk / 115600;
	}
	USART1->control1.transmit_enabled = 1;
	USART1->control1.enabled = 1;
	// USART1->control2.clock_enabled = 1;
	// These USART configs correspond to 115200 8N1.

	CRT<CRTHAL> crt;

	crt.print("running oled test\r\n");
	OLED<OLEDHAL, 128, 64, 8> oled;
	oled.init();

	const u16 center_x = 64;
	const u16 center_y = 32;
	const u16 width = 10;
	const u16 height = 10;

	u16 y = center_y - (height / 2);
	for (u16 x = center_x - (width / 2); x < center_x + (width / 2); ++x) {
		crt.print("setting ", x, ", ", y, "\r\n");
		oled.set(x, y, 1);
	}
	
	oled.show();
	crt.print("oled test done\r\n");

	crt.print("running epd test\r\n");
	epd_test();
	crt.print("epd test done\r\n");

	crt.print("msiclk: ", msiclk, ".\r\n");
	crt.print("usart1 baud rate: ", USART1->baud_rate.rate, "\r\n");
	crt.print("hello world\r\n");

	NVIC->setenable.line5 = 1;
	while (1) {
		if ((TIMER6->counter / 1024) % 2) {
			GPIO_A->set5 = 1;

			for (u32 i = 0; i < 10000; ++i);

			GPIO_A->reset5 = 1;
		} else {
			GPIO_B->set4 = 1;

			for (u32 i = 0; i < 10000; ++i);

			GPIO_B->reset4 = 1;
		}

		for (u32 i = 0; i < 10001; ++i);
	}
}

struct sys_task sys_tasks[] = {
	SYS_TASKS_END,
};
