/**
 * @file i8042.h
 * @brief
 */

#ifndef _IO_I8042_
#define _IO_I8042_

#include "lcom/lcf.h"

#define KBC_IRQ_LINE 1                /** @brief Keyboard Controller IRQ line number */

#define KBC_IN_BUFFER   0x60          /** @brief I/O port: KBC input buffer (data written to controller) */
#define KBC_OUT_BUFFER  0x60          /** @brief I/O port: KBC output buffer (data read from controller) */
#define KBC_STATUS_REG  0x64          /** @brief I/O port: KBC status register (read) */
#define KBC_COMMAND_REG 0x64          /** @brief I/O port: KBC command register (write) */

#define KBC_STATUS_PARITY_BIT  BIT(7) /** @brief Status bit: parity error (1 = parity error) */
#define KBC_STATUS_TIMEOUT_BIT BIT(6) /** @brief Status bit: timeout error (1 = timeout error) */
#define KBC_STATUS_IBF_BIT     BIT(1) /** @brief Status bit: input buffer full (1 = controller busy) */
#define KBC_STATUS_OBF_BIT     BIT(0) /** @brief Status bit: output buffer full (1 = data available) */

#endif                                // _IO_I8042_
