#include "types.h"

#include "isr.h"
#include "hal/arm/registers.h"

extern u32 ld_data_source;
extern u32 ld_data_targetstart;
extern u32 ld_data_targetend;

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

char __aeabi_unwind_cpp_pr0[0];

extern void _start();

static void _check_preconditions() {
	// Check that integer types are the width we expect.
	BUILD_BUG_ON(sizeof(u8) != 1);
	BUILD_BUG_ON(sizeof(u16) != 2);
	BUILD_BUG_ON(sizeof(u32) != 4);
}

void sys_isr_reset() {
	load_data();
	load_bss();

	_start();

	while (1);
}
