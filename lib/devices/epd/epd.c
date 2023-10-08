#include "epd.h"

#include "epd-internal.h"

void devices_epd_init(
  struct devices_epd* epd
) {
  epd->hal->init(epd->hal);

	// Wait for a sec.
	for (int i = 0; i < 10000; i++) {}

	// Disable deep sleep.
	devices_epd_sendcommand1(epd, 0x10, 0x00);
	// Set data direction.
	devices_epd_sendcommand1(epd, 0x11, 0x03);
	// Set display window: X. This has to be (epd.size.x / 4 - 1).
	{
		const u8 data[2] = {0x00, 0x11};
		devices_epd_sendcommand(epd, 68, data, 2);
	}
	// Set display window: Y. This has to be (epd.size.y - 1).
	{
		const u8 data[2] = {0x00, 0xAB};
		devices_epd_sendcommand(epd, 69, data, 2);
	}
	// Set RAM X address.
	devices_epd_sendcommand1(epd, 78, 0x00);
	// Set RAM Y address.
	devices_epd_sendcommand1(epd, 79, 0x00);
	// Booster feedback.
	devices_epd_sendcommand1(epd, 240, 0x1F);
	// Disable RAM Bypass.
	// Set GS transition to GS0 - GS3.
	devices_epd_sendcommand1(epd, 33, 0x03);
	// Write VCOM register.
	devices_epd_sendcommand1(epd, 44, 0xA0);
	// Border waveform.
	devices_epd_sendcommand1(epd, 60, 0x64);
	// Write LUT something
	devices_epd_sendcommand(epd, 50, epd_lut, sizeof(epd_lut));

	devices_epd_refreshandwait(epd);
}

void devices_epd_senddata(
  struct devices_epd* epd,
  const u8* data,
  const u16 data_len) {
  epd->hal->setdc(
    epd->hal,
    DEVICES_EPD_HAL_DC_DATA);
  
	epd->hal->sendserial(
	  epd->hal,
	  data,
	  data_len);
}

void devices_epd_sendcommand(
  struct devices_epd* epd,
  const u8 command,
  const u8* data,
  const u16 data_len) {
  epd->hal->setdc(
    epd->hal,
    DEVICES_EPD_HAL_DC_COMMAND);

  epd->hal->sendserial(
    epd->hal,
    &command,
    1);

	if (data_len) {
		devices_epd_senddata(
		  epd,
		  data,
		  data_len);
	}
}

void devices_epd_draw_xbm1pp(
  struct devices_epd* epd,
  const u8* picture,
  const u16 len) {
	devices_epd_sendcommand(
	  epd,
	  0x24,
	  NULL,
	  0);
	
	for (u16 i = 0, l = len; i < l; ++i) {
		const u8* out = &xbm1bpp_lookup[(picture[i] * 2)];
		devices_epd_senddata(
		  epd,
		  out,
		  2);
	}
}

void devices_epd_wait(
  struct devices_epd* epd
) {
  epd->hal->wait(epd->hal);
}

void devices_epd_refresh(
  struct devices_epd* epd
) {
	// Display update control something
	{
		u8 data = 0xC4;
		devices_epd_sendcommand(epd, 34, &data, 1);
	}

	// // Send a "draw" command.
	devices_epd_sendcommand(epd, 32, NULL, 0);

	// Normally, it might make sense to turn off the power here, but that will
	// end up draining power from the display, causing it to fade.
}

void devices_epd_refreshandwait(
  struct devices_epd* epd
) {
  devices_epd_refresh(epd);
  devices_epd_wait(epd);
}

extern inline void devices_epd_sendcommand0(
  struct devices_epd* epd,
  const u8 command);
extern inline void devices_epd_sendcommand1(
  struct devices_epd* epd,
  const u8 command, const u8 data);
