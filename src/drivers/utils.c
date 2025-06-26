#include "utils.h"
#include "stdint.h"
#include "lcom/lcf.h"

Result util_sys_outb(uint32_t port, uint8_t byte) {
    if (sys_outb(port, byte)) return RES_IO_ERROR;
    return RES_OK;
}

Result util_sys_inb_alt(uint32_t port, uint8_t *byte) {
    if (byte == NULL) return RES_NULL_POINTER;

    uint32_t value;

    if (sys_inb(port, &value)) return RES_IO_ERROR;
    *byte = (uint8_t)value;

    return RES_OK;
}
