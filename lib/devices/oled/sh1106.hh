#pragma once

#include "gfx/font.hh"
#include "std/assert.hh"
#include "std/utf8.hh"
#include "types.h"

namespace devices {
namespace oled {

template <typename HAL, u16 _width, u16 _height>
struct SH1106: public HAL {
	static const u16 width = _width;
	static const u16 height = _height;
	static const u16 page_size_rows = 8;
	static const u16 page_size_bytes = width;
	static const u8 page_count = height / page_size_rows;

	static_assert(
		_height % 8 == 0,
		"SH1106 height must be multiple of 8");
	static_assert(
		_width % 8 == 0,
		"SH1106 width must be multiple of 8");

	static_assert(
		std::assert::SameType<
			decltype(&HAL::init),
			void (HAL::*)()>::value,
		"HAL::init missing");
	
	static_assert(
		std::assert::SameType<
			decltype(&HAL::set_command),
			void (HAL::*)()>::value,
		"HAL::set_command missing");
	
	static_assert(
		std::assert::SameType<
			decltype(&HAL::set_data),
			void (HAL::*)()>::value,
		"HAL::set_data missing");
	
	static_assert(
		std::assert::SameType<
			decltype(&HAL::send),
			void (HAL::*)(const u8*, const u16)>::value,
		"HAL::send_data missing");

	// framebuf is the column-major buffer of data for this screen. The bit for
	// pixel x, y is framebuf[(x * height / 8) + (y / 8)] & (1 << (y % 8)).
	u8 framebuf[width * height / 8] { 0 };

	// start_column_address is the column address to start drawing to. Depending
	// on the specific board, this value may be different.
	u8 start_column_address { 2 };
	
	enum : u8{
		COMMAND_SETLOWCOLUMNADDRESS = 0x00,
		COMMAND_SETHIGHCOLUMNADDRESS = 0x10,
		COMMAND_SETSEGMENTREMAP = 0xA0,
		COMMAND_FORCEDISPLAYON = 0xA5,
		COMMAND_DISPLAYNORMAL = 0xA6,
		COMMAND_DISPLAYREVERSE = 0xA7,
		COMMAND_DISPLAYON = 0xAF,
		COMMAND_SETPAGEADDRESS = 0xB0,
	};

	struct PixelCoordinate {
	  u16 byte;
	  u8 bit;
	};
	
	void init() {
		HAL::init();

		send_command(COMMAND_DISPLAYON);
	}

	PixelCoordinate locate(
	  const u16 x,
	  const u16 y) {
	  return PixelCoordinate {
		  .byte = static_cast<u16>((x * height / 8) + (y / 8)),
		  .bit = static_cast<u8>(y % 8),
	  };
	}

	void set(
		const u16 x,
		const u16 y,
		const u8 value) {
		const PixelCoordinate c = locate(x, y);
		
		if (value) {
			framebuf[c.byte] |= (1 << c.bit);
		} else {
			framebuf[c.byte] &= ~(1 << c.bit);
		}
	}

	void send_page(
		const u8 page_i,
		const u8 (&page)[page_size_bytes]) {
		send_command(COMMAND_SETPAGEADDRESS | page_i);
		send_command(COMMAND_SETLOWCOLUMNADDRESS | start_column_address);
		send_command(COMMAND_SETHIGHCOLUMNADDRESS | 0);

		send_data(page, sizeof(page));
	}

	void clear() {
		const u8 page[page_size_bytes] = {0};
		for (u8 i = 0; i < page_count; ++i) {
			send_page(i, page);
		}
	}

	void draw_text(
		u16 x,
		u16 y,
		const gfx::Font* font,
		const char* text) {
		const u16 base = y;
		u16 glyph_x = x;
		
		do {
			const u32 codepoint = std::utf8::codepoint(&text);
			if (text == nullptr) {
				return;
			}
			if (codepoint == 0) {
				return;
			}
			
			const gfx::Font::Glyph* glyph = font->glyph(codepoint);
			if (glyph == nullptr) {
				return;
			}

			const u8 row_byte_count = (glyph->bounding_box.x / 8) + !!(glyph->bounding_box.x % 8);

			for (i32 row = 0; row < glyph->bounding_box.y; ++row) {
				const i32 y = base - glyph->bounding_box.offset.y - (
					static_cast<i32>(glyph->bounding_box.y) - row - 1);

				if (y < 0 || y >= height) {
					continue;
				}

				for (i32 column = 0; column < glyph->bounding_box.x; ++column) {
					const i32 x = glyph_x + glyph->bounding_box.offset.x + column;

					if (x < 0 || x >= width) {
						continue;
					}

					// MSB of each bitmap row is leftmost column.
					const u8 b = glyph->bitmap[(row * row_byte_count) + (column / 8)];
					const u8 shift = 7 - (column % 8);

					set(x, y, ((b & (1 << shift)) >> shift) & 1);
				}
			}

			glyph_x += glyph->advance.x;
		} while (true);
	}

	void show() {
		// framebuf is held as a simple bitmap of the desired image on the screen,
		// but the SH1106 requires pixel data to be sent in pages, where each page
		// is 8 rows, and each byte sent is one column. So we can't just blit the
		// framebuf to the controller, we need to do some math. Luckily, framebuf
		// is column-major, so we just need to make sure we send the right
		// bytes.

		u8 page[page_size_bytes] = {0};
		for (u8 page_i = 0; page_i < page_count; ++page_i) {
			for (u16 col = 0; col < width; ++col) {
				page[col] = framebuf[page_i + (col * page_count)];
			}

			send_page(page_i, page);
		}
	}

	void send_command(const u8 command) {
		HAL::set_command();
		HAL::send(&command, sizeof(command));
	}

	void send_data(
		const u8* data,
		const u16 len) {
		HAL::set_data();
		HAL::send(data, len);
	}

	SH1106() = default;
	SH1106(const SH1106&) = delete;
	SH1106(SH1106&&) = default;
};

}
}
