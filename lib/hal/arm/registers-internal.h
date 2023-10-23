#pragma once

#define MCU_DECLARE_REGISTER(name, type) extern volatile type* const name

#define MCU_DEFINE_REGISTER(address, name, type) volatile type* const name = (volatile type* const) address
