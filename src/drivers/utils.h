#ifndef _IO_UTILS_
#define _IO_UTILS_

// IO Utils
#include "../utils/result.h"
#include "minix/syslib.h"
#include "stdint.h"

#define BIT(n) (1 << n)

Result util_sys_outb(int32_t port, u8_t byte) {
    if (sys_outb(port, byte)) return RES_IO_ERROR;
    return RES_OK;
}

Result util_sys_inb(int32_t port, u8_t *byte) {
    uint32_t value;

    if (sys_inb(port, &value)) return RES_IO_ERROR;
    *byte = (uint8_t)value;

    return RES_OK;
}

#endif // _IO_UTILS_
