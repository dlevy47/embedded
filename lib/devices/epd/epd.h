#pragma once

#include "types.h"

// enum devices_epd_hal_dc contains the valid values for the data/command pin.
enum devices_epd_hal_dc {
  DEVICES_EPD_HAL_DC_DATA,
  DEVICES_EPD_HAL_DC_COMMAND,
};

// struct devices_epd_hal contains function pointers to functionality required
// by the epd driver.
struct devices_epd_hal {
  // init should configure connected pins as appropriate.
  void (*init) (
    struct devices_epd_hal* self
  );

  // set_dc sets the data/command pin as required.
  void (*setdc) (
    struct devices_epd_hal* self,
    enum devices_epd_hal_dc dc
  );

  // send_serial sends data via serial to the epd.
  void (*sendserial) (
    struct devices_epd_hal* self,
    const u8* data,
    const u16 len
  );

  // wait waits for the epd to not be busy.
  void (*wait) (
    struct devices_epd_hal* self
  );
};

// struct devices_epd contains configuration information for a specific epd.
struct devices_epd {
  // hal is the layer used to communicate directly with hardware.
  struct devices_epd_hal* hal;
};

// devices_epd_init runs through the initialization sequence for the epd.
void devices_epd_init(
  struct devices_epd* epd
);

// devices_epd_senddata sends a chunk of data using DMA.
void devices_epd_senddata(
  struct devices_epd* epd,
  const u8* data,
  const u16 data_len);

// devices_epd_sendcommand sends a command with optional data.
void devices_epd_sendcommand(
  struct devices_epd* epd,
  const u8 command,
  const u8* data,
  const u16 data_len);

// devices_epd_sendcommand0 is a helper function to send commands with no data.
inline void devices_epd_sendcommand0(
  struct devices_epd* epd,
  const u8 command) {
  devices_epd_sendcommand(
    epd,
    command,
    NULL,
    0);
}

// devices_epd_sendcommand1 is a helper function to send commands with one
// byte of data.
inline void devices_epd_sendcommand1(
  struct devices_epd* epd,
  const u8 command,
  const u8 data) {
  devices_epd_sendcommand(
    epd,
    command,
    &data,
    1);
}

// devices_epd_draw_xbm1pp draws a 1 bit-per-pixel XBM bitmap.
void devices_epd_draw_xbm1pp(
  struct devices_epd* epd,
  const u8* picture,
  const u16 len);

// devices_epd_wait waits for the epd to be not busy.
void devices_epd_wait(
  struct devices_epd* epd
);

// devices_epd_refresh sends a draw command to the epd.
void devices_epd_refresh(
  struct devices_epd* epd
);

// devices_epd_refreshandwait refreshes the epd and waits for it to finish.
void devices_epd_refreshandwait(
  struct devices_epd* epd
);
