/**
 * @file drivers/utils.h
 * @brief Utility functions and macros for I/O operations and data manipulation.
 */

#ifndef _IO_UTILS_
#define _IO_UTILS_

#include "../utils/result.h"
#include "stdint.h"

// /**
//  * @brief Create a bit mask with bit n set.
//  * @param n The bit position to set (0-based).
//  */
// #define BIT(n) (1 << n)

/**
 * @brief Write a byte to the specified I/O port.
 * @param port The I/O port address.
 * @param byte The byte value to write.
 * @return RES_OK on success, otherwise an error code.
 */
Result util_sys_outb(uint32_t port, uint8_t byte);

/**
 * @brief Read a byte from the specified I/O port.
 * @param port The I/O port address.
 * @param byte Pointer to store the read byte.
 * @return RES_OK on success, RES_NULL_POINTER if byte is NULL,
 *         or RES_IO_ERROR on I/O failure.
 */
Result util_sys_inb_alt(uint32_t port, uint8_t *byte);

/**
 * @brief Extract the least significant byte from a 16-bit value.
 * @param val The 16-bit input value.
 * @param lsb Pointer to store the least significant byte.
 * @return RES_OK on success, or RES_NULL_POINTER if lsb is NULL.
 */
Result util_get_LSB_alt(uint16_t val, uint8_t *lsb);

/**
 * @brief Extract the most significant byte from a 16-bit value.
 * @param val The 16-bit input value.
 * @param msb Pointer to store the most significant byte.
 * @return RES_OK on success, or RES_NULL_POINTER if msb is NULL.
 */
Result util_get_MSB_alt(uint16_t val, uint8_t *msb);

#endif // _IO_UTILS_
