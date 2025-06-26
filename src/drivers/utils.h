#ifndef _IO_UTILS_
#define _IO_UTILS_

// IO Utils
#include "../utils/result.h"
#include "stdint.h"

#define BIT(n) (1 << n)

Result util_sys_outb(uint32_t port, uint8_t byte);

Result util_sys_inb_alt(uint32_t port, uint8_t *byte);

#endif // _IO_UTILS_
