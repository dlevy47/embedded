#pragma once

#include "types.hh"

namespace devices {
namespace epd {

// epd_lut is the LUT sent to the EPD on initialization.
extern const u8 epd_lut[90];

// xbm1bpp_lookup is a lookup table from a 1 bit-per-pixel XBM
// bitmap to the two bytes that need to be send to the epd per XBM byte.
extern const u8 xbm1bpp_lookup[256 * 2];

template <typename HAL>
struct EPD: public HAL {
  // init runs through the initialization sequence for the epd.
  void init() {
    HAL::init();

	  // Disable deep sleep.
	  send_command(0x10, 0x00);
	  // Set data direction.
	  send_command(0x11, 0x03);
	  // Set display window: X. This has to be (epd.size.x / 4 - 1).
	  {
		  const u8 data[2] = {0x00, 0x11};
		  send_command(68, data, 2);
	  }
	  // Set display window: Y. This has to be (epd.size.y - 1).
	  {
		  const u8 data[2] = {0x00, 0xAB};
		  send_command(69, data, 2);
	  }
	  // Set RAM X address.
	  send_command(78, 0x00);
	  // Set RAM Y address.
	  send_command(79, 0x00);
	  // Booster feedback.
	  send_command(240, 0x1F);
	  // Disable RAM Bypass.
	  // Set GS transition to GS0 - GS3.
	  send_command(33, 0x03);
	  // Write VCOM register.
	  send_command(44, 0xA0);
	  // Border waveform.
	  send_command(60, 0x64);
	  // Write LUT something
	  send_command(50, epd_lut, sizeof(epd_lut));

	  refresh_and_wait();
  }

  // send_data sends a chunk of data using DMA.
  void send_data(
    const u8* data,
    const u16 data_len
  ) {
    HAL::set_data();

    HAL::send(
      data,
      data_len);
  }

  // send_command sends a command with no data.
  void send_command(
    const u8 command
  ) {
    send_command(
      command,
      nullptr,
      0);
  }
  
  // send_command sends a command with a single byte of data.
  void send_command(
    const u8 command,
    const u8 data
  ) {
    send_command(
      command,
      &data,
      1);
  }
  
  // send_command sends a command with a chunk of data using DMA.
  void send_command(
    const u8 command,
    const u8* data,
    const u16 data_len
  ) {
    HAL::set_command();

    HAL::send(
      &command,
      1);

    if (data) {
      send_data(
        data,
        data_len);
    }
  }

// draw_xbm1pp draws a 1 bit-per-pixel XBM bitmap.
  void draw_xbm1pp(
    const u8* picture,
    const u16 len
  ) {
    send_command(0x24);

	  for (u16 i = 0, l = len; i < l; ++i) {
		  const u8* out = &xbm1bpp_lookup[(picture[i] * 2)];
		  send_data(out, 2);
	  }
  }

  // wait waits for the epd to be not busy.
  void wait() {
    HAL::wait();
  }

  // refresh sends a draw command to the epd.
  void refresh() {
	  // Display update control something
	  {
		  u8 data = 0xC4;
		  send_command(34, &data, 1);
	  }

	  // // Send a "draw" command.
	  send_command(32);

	  // Normally, it might make sense to turn off the power here, but that will
	  // end up draining power from the display, causing it to fade.
  }

  // refresh_and_wait refreshes the epd and waits for it to finish.
  void refresh_and_wait() {
    refresh();
    wait();
  }

  // is_busy returns whether the EPD is busy (e.g. in a refresh cycle).
  bool is_busy() {
    return HAL::is_busy();
  }
};

}
}
