#pragma once

#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @brief Tests display of timer config
 *
 * Just calls timer_get_conf() followed by timer_display_conf()
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbd_test_scan)();

/**
 * @brief Tests display of timer config
 *
 * Just calls timer_get_conf() followed by timer_display_conf()
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbd_test_poll)();

/**
 * @brief Tests display of timer config
 *
 * Just calls timer_get_conf() followed by timer_display_conf()
 *
 * @param n  Configuration field to display
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbd_test_timed_scan)(uint8_t n);
