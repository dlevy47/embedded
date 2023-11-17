#include "epd.hh"
#include "oled.hh"
#include "picture.hh"

static u32 color = 0;

static void button_handler() {
	color = !color;

	MCU::EXTI->pending.line0 = 1;
}

// delay waits for the specified number of 1/1024s of a second to elapse.
static void delay(u32 mibis) {
	MCU::TIMER6->control1.one_pulse_mode = 1;
}

extern "C" void app_main() {
	sys::isr::user_vector[5] = button_handler;

	// For UART, configure 115200 8N1:
	//   115200 baud rate
	//   8 bit data
	//   Odd parity
	//   1 stop bit

	// Enable interrupt handling for PA0 input.
	//   Reference 13.4: PA0 -> EXTI0
	//   Reference 12.3: EXTI0 and EXTI1 interrupts map to IRQ 5
	MCU::EXTI->interrupt.line0 = 1;
	MCU::EXTI->rising.line0 = 1;
	MCU::NVIC->setenable.line5 = 1;

	// Enable GPIOA and GPIOB clocks.
	MCU::RCC->gpio_enable.a = 1;
	MCU::RCC->gpio_enable.b = 1;

	// Enable SPI1, SPI2, and DMA clocks.
	MCU::RCC->apb1_enable.spi2 = 1;
	MCU::RCC->apb2_enable.spi1 = 1;
	MCU::RCC->ahb_enable.dma = 1;

	// Enable USART1 clock.
	MCU::RCC->apb2_enable.usart1 = 1;

	// Enable TIMER6 clock.
	MCU::RCC->apb1_enable.timer6 = 1;
	MCU::DBG_APB1_FREEZE->timer6 = 1;

	// Enable PA0 for input.
	MCU::GPIO_A->mode.pin0 = mcu::arm::GPIO::Mode::INPUT;

	// Enable PA8, and PA9 for USART output.
	// NOTE: It's important to set the alternate function index first, because
	// otherwise the pin will have a short period when it is enabled, but not
	// connected to the USART, and spurious data will be sent.
	MCU::GPIO_A->alternate.pin8 = 4;
	MCU::GPIO_A->mode.pin8 = mcu::arm::GPIO::Mode::ALTERNATE;
	MCU::GPIO_A->output_type.pin8 = mcu::arm::GPIO::OutputType::PUSHPULL;
	MCU::GPIO_A->alternate.pin9 = 4;
	MCU::GPIO_A->mode.pin9 = mcu::arm::GPIO::Mode::ALTERNATE;
	MCU::GPIO_A->output_type.pin9 = mcu::arm::GPIO::OutputType::PUSHPULL;

	// Enable PA5 and PB4 for output.
	// On the dev board, these correspond to the red and green LEDs.
	MCU::GPIO_A->mode.pin5 = mcu::arm::GPIO::Mode::OUTPUT;
	MCU::GPIO_B->mode.pin4 = mcu::arm::GPIO::Mode::OUTPUT;
	
	MCU::GPIO_B->mode.pin6 = mcu::arm::GPIO::Mode::OUTPUT;
	MCU::GPIO_B->output_speed.pin6 = mcu::arm::GPIO::OutputSpeed::VERYHIGH;

	// TIMER6 is an APB1 peripheral, and so uses the PCLK1 clock source.
	// The PCLK1 frequency is the prescaled HCLK frequency.
	// The HCLK frequency is the prescaled SYSCLK frequency.
	// The SYSCLK frequency is determined from RCC->clock_configuration.clock_switch_status.
	//   On reset, it is the MSICLK frequency.
	// The MSICLK frequency is determined from 32768 * (1 << RCC->clock_calibration.msi_range + 1).
	u32 msiclk = 32768 * (1 << (MCU::RCC->clock_calibration.msi_range + 1));
	// For now, elide the prescaling (because we know what our values are).
	u32 pclk1 = msiclk;

	// Enable TIMER6.
	MCU::TIMER6->control1.enable_counter = 1;
	MCU::TIMER6->prescaler = pclk1 / 1024;
	// After application of the prescaler, TIMER6's values should be 1/1024 of a second.

	// Configure USART1.
	if (MCU::USART1->control1.over8) {
		MCU::USART1->baud_rate.rate = 2 * msiclk / 115600;
	} else {
		MCU::USART1->baud_rate.rate = msiclk / 115600;
	}
	MCU::USART1->control1.transmit_enabled = 1;
	MCU::USART1->control1.enabled = 1;
	// USART1->control2.clock_enabled = 1;
	// These USART configs correspond to 115200 8N1.

	_crt.print("msiclk: ", msiclk, ".\r\n");
	_crt.print("usart1 baud rate: ", MCU::USART1->baud_rate.rate, "\r\n");
	_crt.print("hello world\r\n");
	_crt.print("こんにちは\r\n");

	_crt.print("starting scheduler\r\n");

	u32 blink_stack[600];
	os::Task blink_task {
		"blink",
		blink_stack,
		blink,
	};

	static_assert(
		sizeof(blink_stack) > sizeof(devices::oled::SH1106<OLEDHAL, 128, 64>),
		"blink_stack not big enough for oled framebuf"
	);

	u32 epd_test_stack[300];
	os::Task epd_test_task {
		"epd_test",
		epd_test_stack,
		epd_test,
	};

	os::Task<Scheduler> tasks[] = {
		blink_task,
		epd_test_task,
	};

	Scheduler scheduler(tasks);

	for (size_t i = 0, l = sizeof(tasks) / sizeof(*tasks); i < l; ++i) {
		os::Task<Scheduler>* task = &tasks[i];
		
		_crt.print("task ", task->name, " stack ",
						"from ", task->stack_limit, " ",
						"to ", task->stack_top, "\r\n");
	}

	_crt.print("task ", scheduler.control[0].scheduler_task.name, " stack ",
					 "from ", scheduler.control[0].scheduler_task.stack_limit, " ",
					 "to ", scheduler.control[0].scheduler_task.stack_top, "\r\n");

	scheduler.run();

	_crt.print("no more scheduler\r\n");
}
