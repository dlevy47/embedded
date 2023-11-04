#include "epd.hh"
#include "oled.hh"
#include "picture.hh"

static u32 color = 0;

static void button_handler() {
	color = !color;

	mcu::EXTI->pending.line0 = 1;
}

// delay waits for the specified number of 1/1024s of a second to elapse.
static void delay(u32 mibis) {
	mcu::TIMER6->control1.one_pulse_mode = 1;
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
	mcu::EXTI->interrupt.line0 = 1;
	mcu::EXTI->rising.line0 = 1;
	mcu::NVIC->setenable.line5 = 1;

	// Enable GPIOA and GPIOB clocks.
	mcu::RCC->gpio_enable.a = 1;
	mcu::RCC->gpio_enable.b = 1;

	// Enable SPI1, SPI2, and DMA clocks.
	mcu::RCC->apb1_enable.spi2 = 1;
	mcu::RCC->apb2_enable.spi1 = 1;
	mcu::RCC->ahb_enable.dma = 1;

	// Enable USART1 clock.
	mcu::RCC->apb2_enable.usart1 = 1;

	// Enable TIMER6 clock.
	mcu::RCC->apb1_enable.timer6 = 1;
	mcu::DBG_APB1_FREEZE->timer6 = 1;

	// Enable PA0 for input.
	mcu::GPIO_A->mode.pin0 = hal::arm::GPIO::Mode::INPUT;

	// Enable PA8, and PA9 for USART output.
	// NOTE: It's important to set the alternate function index first, because
	// otherwise the pin will have a short period when it is enabled, but not
	// connected to the USART, and spurious data will be sent.
	mcu::GPIO_A->alternate.pin8 = 4;
	mcu::GPIO_A->mode.pin8 = hal::arm::GPIO::Mode::ALTERNATE;
	mcu::GPIO_A->output_type.pin8 = hal::arm::GPIO::OutputType::PUSHPULL;
	mcu::GPIO_A->alternate.pin9 = 4;
	mcu::GPIO_A->mode.pin9 = hal::arm::GPIO::Mode::ALTERNATE;
	mcu::GPIO_A->output_type.pin9 = hal::arm::GPIO::OutputType::PUSHPULL;

	// Enable PA5 and PB4 for output.
	// On the dev board, these correspond to the red and green LEDs.
	mcu::GPIO_A->mode.pin5 = hal::arm::GPIO::Mode::OUTPUT;
	mcu::GPIO_B->mode.pin4 = hal::arm::GPIO::Mode::OUTPUT;
	
	mcu::GPIO_B->mode.pin6 = hal::arm::GPIO::Mode::OUTPUT;
	mcu::GPIO_B->output_speed.pin6 = hal::arm::GPIO::OutputSpeed::VERYHIGH;

	// TIMER6 is an APB1 peripheral, and so uses the PCLK1 clock source.
	// The PCLK1 frequency is the prescaled HCLK frequency.
	// The HCLK frequency is the prescaled SYSCLK frequency.
	// The SYSCLK frequency is determined from RCC->clock_configuration.clock_switch_status.
	//   On reset, it is the MSICLK frequency.
	// The MSICLK frequency is determined from 32768 * (1 << RCC->clock_calibration.msi_range + 1).
	u32 msiclk = 32768 * (1 << (mcu::RCC->clock_calibration.msi_range + 1));
	// For now, elide the prescaling (because we know what our values are).
	u32 pclk1 = msiclk;

	// Enable TIMER6.
	mcu::TIMER6->control1.enable_counter = 1;
	mcu::TIMER6->prescaler = pclk1 / 1024;
	// After application of the prescaler, TIMER6's values should be 1/1024 of a second.

	// Configure USART1.
	if (mcu::USART1->control1.over8) {
		mcu::USART1->baud_rate.rate = 2 * msiclk / 115600;
	} else {
		mcu::USART1->baud_rate.rate = msiclk / 115600;
	}
	mcu::USART1->control1.transmit_enabled = 1;
	mcu::USART1->control1.enabled = 1;
	// USART1->control2.clock_enabled = 1;
	// These USART configs correspond to 115200 8N1.

	_crt.print("msiclk: ", msiclk, ".\r\n");
	_crt.print("usart1 baud rate: ", mcu::USART1->baud_rate.rate, "\r\n");
	_crt.print("hello world\r\n");
	_crt.print("こんにちは\r\n");

	_crt.print("starting scheduler\r\n");

	// Do the tasks need a reference to the scheduler? For yield, etc
	// Or perhaps they can be provided with one

	u32 blink_stack[400];
	os::Task blink_task {
		"blink",
		blink_stack,
		blink,
	};

	static_assert(
		sizeof(blink_stack) > sizeof(devices::oled::SH1106<OLEDHAL, 128, 64>),
		"blink_stack not big enough for oled framebuf"
	);

	u32 epd_test_stack[400];
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

	_crt.print("scheduler: ", &scheduler, "\r\n");
	_crt.print("task_ended: ", &scheduler.task_ended, "\r\n");
	_crt.print("cpu_index: ", &SchedulerHAL::cpu_index, "\r\n");
	_crt.print("control address: ", &scheduler.control, "\r\n");
	_crt.print("  current address: ", &scheduler.control[0].current, "\r\n");
	_crt.print("  next address: ", &scheduler.control[0].next, "\r\n");

	for (size_t i = 0, l = sizeof(tasks) / sizeof(*tasks); i < l; ++i) {
		os::Task<Scheduler>* task = &tasks[i];
		
		_crt.print("task ", task->name, " stack ",
						"from ", task->stack_top, " ",
						"to ", task->stack_bottom, "\r\n");
	}

	_crt.print("task ", scheduler.control[0].scheduler_task.name, " stack ",
					 "from ", scheduler.control[0].scheduler_task.stack_top, " ",
					 "to ", scheduler.control[0].scheduler_task.stack_bottom, "\r\n");

	scheduler.run();

	_crt.print("no more scheduler\r\n");
}
