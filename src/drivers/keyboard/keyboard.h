#ifndef _IO_KEYBOARD_
#define _IO_KEYBOARD_

#include "KBC.h"

#define KEYBOARD_2BYTE_CODE 0xE0

/**
 * @brief   Subscribes to KBC interrupts.
 * @param   bit_no  Out: pointer to store the IRQ bit number for the KBC.
 * @return  RES_OK on success or an error code on failure.
 */
Result keyboard_subscribe_int(uint8_t *bit_no);

/**
 * @brief   Unsubscribes from KBC interrupts.
 * @return  RES_OK on success or an error code on failure.
 */
Result keyboard_unsubscribe_int();

/**
 * @brief   Keyboard interrupt handler: reads scancode byte(s) from the KBC.
 * @param   scancode  Out: pointer to receive the assembled scancode (1 or 2 bytes).
 * @return  RES_OK         on successful read of a complete scancode,
 *          RES_NOT_READY  if this was the first byte of a two-byte scancode,
 *          RES_IO_ERROR   on I/O errors, or other error codes.
 */
Result keyboard_ih(uint16_t *scancode);

/**
 * @brief   Polls the keyboard by manually reading a scancode without using interrupts.
 * @param   scancode  Out: pointer to receive the assembled scancode (1 or 2 bytes).
 * @return  RES_OK         on successful read of a complete scancode,
 *          RES_NOT_READY  if this was the first byte of a two-byte scancode,
 *          RES_IO_ERROR   on I/O errors, or other error codes.
 */
Result keyboard_poll(uint16_t *scancode);

/**
 * @brief   Restores keyboard interrupts by setting the interrupt‐enable bit in the KBC command byte.
 * @return  RES_OK on success or an error code on failure.
 */
Result keyboard_restore();

#endif // _IO_KEYBOARD_
