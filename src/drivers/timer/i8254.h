#ifndef _IO_I8254_
#define _IO_I8254_

/**
 * @file i8254.h
 * @brief Intel 8254 Programmable Interval Timer (PIT) register and control definitions
 */

#include "../utils.h"
#include "stdbool.h"
#include "stdint.h"

#define TIMER_IRQ_LINE  0                          /** @brief Timer IRQ Line number */
#define TIMER_FREQUENCY 1193182                    /** @brief Clock frequency of timer counter */

#define TIMER_0_REG    0x40                        /** @brief Channel 0 data port */
#define TIMER_1_REG    0x41                        /** @brief Channel 1 data port */
#define TIMER_2_REG    0x42                        /** @brief Channel 2 data port */
#define TIMER_CTRL_REG 0x43                        /** @brief Control word port */

#define CTRL_SELECT_TIMER_0 0x00                   /** @brief Select timer channel 0 */
#define CTRL_SELECT_TIMER_1 BIT(6)                 /** @brief Select timer channel 1 */
#define CTRL_SELECT_TIMER_2 BIT(7)                 /** @brief Select timer channel 2 */

#define CTRL_LSB          BIT(4)                   /** @brief Input least significant byte only */
#define CTRL_MSB          BIT(5)                   /** @brief Input most significant byte only */
#define CTRL_LSB_MSB      (BIT(5) | BIT(4))        /** @brief Input least then most significant byte */
#define CTRL_LSB_MSB_MASK (BIT(5) | BIT(4))        /** @brief Input mode mask */

#define CTRL_MODE_0     0x00                       /** @brief Mode 0: Interrupt on terminal count */
#define CTRL_MODE_1     BIT(1)                     /** @brief Mode 1: Hardware re-triggerable one-shot */
#define CTRL_MODE_2     BIT(2)                     /** @brief Mode 2: Rate generator */
#define CTRL_MODE_2_ALT (BIT(3) | BIT(2))          /** @brief Mode 2: Rate generator | Alternative form */
#define CTRL_MODE_3     (BIT(2) | BIT(1))          /** @brief Mode 3: Square wave generator */
#define CTRL_MODE_3_ALT (BIT(3) | BIT(2) | BIT(1)) /** @brief Mode 3: Square wave generator | Alternative form*/
#define CTRL_MODE_4     BIT(3)                     /** @brief Mode 4: Software triggered strobe */
#define CTRL_MODE_5     (BIT(3) | BIT(1))          /** @brief Mode 5: Hardware triggered strobe */
#define CTRL_MODE_MASK  (BIT(3) | BIT(2) | BIT(1)) /** @brief Couting mode mask */

#define CTRL_NOT_BCD  0x00                         /** @brief 16-bit binary counter */
#define CTRL_BCD      BIT(0)                       /** @brief Four-digit BCD counter */
#define CTRL_BCD_MASK BIT(0)                       /** @brief BCD option mask */

#endif                                             // _IO_I8254_
