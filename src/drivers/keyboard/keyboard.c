#include "keyboard.h"
#include "lcom/lcf.h"

int32_t KBC_hook_id  = 1;
bool    completeScan = true;

Result keyboard_subscribe_int(uint8_t *bit_no) {
    if (bit_no == NULL) return RES_NULL_POINTER;

    uint8_t temp_bit_no = KBC_hook_id;
    if (sys_irqsetpolicy(KBC_IRQ_LINE, IRQ_REENABLE | IRQ_EXCLUSIVE, &KBC_hook_id)) return RES_KERNEL_ERROR;

    *bit_no = temp_bit_no;
    return RES_OK;
}

Result keyboard_unsubscribe_int() {
    if (sys_irqrmpolicy(&KBC_hook_id)) return RES_KERNEL_ERROR;
    return RES_OK;
}

Result keyboard_ih(uint16_t *scancode) {
    // Read KBC status and output byte
    KBCStatus status;
    KBCOutput scanCodeByte;
    RETURN_IF_ERROR(KBC_read_status(&status));
    RETURN_IF_ERROR(KBC_read_output(&scanCodeByte));

    // Sanity check
    if (scancode == NULL) return RES_NULL_POINTER;

    // Check for errors in the status byte
    if (KBC_error(status)) return RES_IO_ERROR;

    // Check if this is the first byte of a 2 byte scancode
    if (scanCodeByte == KEYBOARD_2BYTE_CODE) {
        completeScan = false;
        return RES_NOT_READY;
    }

    // In case this is the second byte received
    // Reconstruct full scancode
    if (!completeScan) {
        completeScan = true;
        *scancode    = (KEYBOARD_2BYTE_CODE << 8) | scanCodeByte;
    } else *scancode = (0x00 << 8) | scanCodeByte;

    return RES_OK;
}

Result keyboard_poll(uint16_t *scancode) { return keyboard_ih(scancode); }

Result keyboard_restore() {
    KBCCommand commandByte;
    RETURN_IF_ERROR(KBC_read_command_byte(&commandByte));

    commandByte |= KBC_COMMAND_BYTE_KEYBOARD_INT_BIT;

    RETURN_IF_ERROR(KBC_write_command_with_arg(KBC_WRITE_COMMAND_BYTE_COMMAND, commandByte));
    return RES_OK;
}
