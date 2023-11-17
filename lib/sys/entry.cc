#include "types.hh"

#include "isr.hh"

extern u32 ld_data_source;
extern u32 ld_data_targetstart;
extern u32 ld_data_targetend;

extern u32 ld_init_array_start;
extern u32 ld_init_array_end;

extern u32 ld_bss_start;
extern u32 ld_bss_end;

static void load_data() {
	u32* from = &ld_data_source;
	u32* to = &ld_data_targetstart;

	while (to < &ld_data_targetend)
		*to++ = *from++;
}

static void load_bss() {
	u32* cur = &ld_bss_start;

	while (cur < &ld_bss_end)
		*cur++ = 0;
}

static void run_static_constructors() {
	u32* start = (u32*) &ld_init_array_start;
	const u32* end = (u32*) &ld_init_array_end;

	for (; start < end; ++start) {
		typedef void (*Constructor) ();
		Constructor ctor = (Constructor) *start;
		
		ctor();
	}
}

extern "C" void app_main();

// Check that integer types are the width we expect.
static_assert(
	sizeof(u8) == 1,
	"sizeof(u8) != 1");
static_assert(
	sizeof(u16) == 2,
	"sizeof(u16) != 2");
static_assert(
	sizeof(u32) == 4,
	"sizeof(u32) != 4");

extern "C" void sys_isr_reset() {
	load_data();
	load_bss();
	run_static_constructors();

	app_main();

  // This loop must include an empty __asm statement so that the compiler
  // doesn't optimize it away.
	while (true) {
		__asm volatile("");
	}
}
