#include "epd.h"

#include "hal/arm/stm32l0538.h"

#include "main.h"

static void epd_init(
	struct devices_epd_hal* hal
) {
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

static void epd_setdc(
	struct devices_epd_hal* hal,
	enum devices_epd_hal_dc dc
) {
	switch (dc) {
		case DEVICES_EPD_HAL_DC_DATA:
			// Data: D/C high.
			GPIO_B->set11 = 1;
			break;
		case DEVICES_EPD_HAL_DC_COMMAND:
			// Command: D/C low.
			GPIO_B->reset11 = 1;
			break;
	}
}

static void epd_sendserial(
	struct devices_epd_hal* hal,
	const u8* data,
	const u16 len) {
	spi1_send(data, len);
}

static void epd_wait(
	struct devices_epd_hal* hal
) {
	while (GPIO_A->input.pin8);
}

static struct devices_epd_hal epd_hal = {
	.init = epd_init,
	.setdc = epd_setdc,
	.sendserial = epd_sendserial,
	.wait = epd_wait,
};

struct devices_epd epd = {
	.hal = &epd_hal,
};
