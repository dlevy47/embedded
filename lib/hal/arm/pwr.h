#pragma once

#include "types.h"

struct pwr_cr {
	u32 _padding:8;
	u32 disable_backup_write_protection:1;
	u32 _padding2:23;
};
