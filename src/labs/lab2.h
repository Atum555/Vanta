#pragma once

#include "lcom/timer.h"
#include <stdint.h>

/**
 * @brief Tests display of timer config
 *
 * Just calls timer_get_conf_alt() followed by timer_display_conf_alt()
 *
 * @param timer Timer whose config to read (Ranges from 0 to 2)
 * @param field Configuration field to display
 * @return Return 0 upon success and non-zero otherwise
 */
int(timer_test_read_config)(uint8_t timer, enum timer_status_field field);

/**
 * @brief Tests change of Timer O interrupt frequency
 *
 * Programs Timer 0 to generate interrupts with input frequency
 *
 * @param timer Timer whose time-base should be changed (Ranges from 0 to 2)
 * @param freq  Frequency of interrupts to generate
 * @return Return 0 upon success and non-zero otherwise
 */
int(timer_test_time_base)(uint8_t timer, uint32_t freq);

/**
 * @brief Tests Timer 0 interrupt handling
 *
 * Subscribes Timer 0 interrupts and prints a message once
 *  per second for the specified time interval in seconds
 *
 * @param time Length, in seconds, of time interval while interrupts are subscribed
 * @return Return 0 upon success and non-zero otherwise
 */
int(timer_test_int)(uint8_t time);
