#ifndef _IO_TIMER_
#define _IO_TIMER_

// Timer - Device Driver
#include "../../utils/result.h"
#include "../utils.h"
#include "i8254.h"
#include "lcom/lcf.h"
#include "lcom/timer.h"

/**
 * @enum  Timer
 * @brief Identifies one of the three PIT timer channels.
 */
typedef enum { TIMER_0 = 0, TIMER_1, TIMER_2 } Timer;

/**
 * @enum  TimerInitMode
 * @brief Specifies how the timer count is loaded.
 */
typedef enum { LSB = 0, MSB, LSB_MSB } TimerInitMode;

/**
 * @enum  TimerCountingMode
 * @brief Defines the counting/operating mode of the PIT.
 */
typedef enum { MODE_0 = 0, MODE_1, MODE_2, MODE_3, MODE_4, MODE_5 } TimerCountingMode;

/**
 * @enum  TimerBCDMode
 * @brief Selects binary or BCD counter format.
 */
typedef enum { NOT_BCD_MODE = 0, BCD_MODE } TimerBCDMode;

/**
 * @typedef TimerStatus
 * @brief   Raw status byte returned by the PIT.
 */
typedef uint8_t TimerStatus;

/**
 * @typedef TimerCtrlWord
 * @brief   Control word used to configure the PIT.
 */
typedef uint8_t TimerCtrlWord;

/**
 * @brief   Get the I/O port address for the specified timer channel.
 * @param   timer  The timer channel (TIMER_0..TIMER_2).
 * @return  I/O port register for the timer.
 */
static inline uint8_t timer_to_reg(Timer timer) { return TIMER_0_REG + timer; }

/**
 * @brief   Build a PIT control word to set mode and format.
 * @param   timer        Channel to configure.
 * @param   initMode     Load mode (LSB, MSB, LSB_MSB).
 * @param   countingMode Counting/operation mode.
 * @param   bcdMode      Binary or BCD counting.
 * @param   word         Out: assembled control word.
 * @return  RES_OK or error code.
 */
static inline Result timer_ctrl_word(
    Timer timer, TimerInitMode initMode, TimerCountingMode countingMode, TimerBCDMode bcdMode, TimerCtrlWord *word
) {
    if (word == NULL) return RES_NULL_POINTER;
    TimerCtrlWord temp_word = 0x00;

    switch (timer) {
    case TIMER_0: temp_word |= CTRL_SELECT_TIMER_0; break;
    case TIMER_1: temp_word |= CTRL_SELECT_TIMER_1; break;
    case TIMER_2: temp_word |= CTRL_SELECT_TIMER_2; break;
    default     : return RES_INVALID_ARGUMENT;
    }

    switch (initMode) {
    case LSB    : temp_word |= CTRL_LSB; break;
    case MSB    : temp_word |= CTRL_MSB; break;
    case LSB_MSB: temp_word |= CTRL_LSB_MSB; break;
    default     : return RES_INVALID_ARGUMENT;
    }

    switch (countingMode) {
    case MODE_0: temp_word |= CTRL_MODE_0; break;
    case MODE_1: temp_word |= CTRL_MODE_1; break;
    case MODE_2: temp_word |= CTRL_MODE_2; break;
    case MODE_3: temp_word |= CTRL_MODE_3; break;
    case MODE_4: temp_word |= CTRL_MODE_4; break;
    case MODE_5: temp_word |= CTRL_MODE_5; break;
    default    : return RES_INVALID_ARGUMENT;
    }

    switch (bcdMode) {
    case NOT_BCD_MODE: temp_word |= CTRL_NOT_BCD; break;
    case BCD_MODE    : temp_word |= CTRL_BCD; break;
    default          : return RES_INVALID_ARGUMENT;
    }

    *word = temp_word;
    return RES_OK;
}

/**
 * @brief   Create a readback command to query count/status.
 * @param   count  true to latch count, false to ignore.
 * @param   status true to latch status, false to ignore.
 * @param   t_0    true to select timer0, etc.
 * @param   t_1    ...
 * @param   t_2    ...
 * @return  Control word for readback.
 */
static inline TimerCtrlWord timer_readback_command(bool count, bool status, bool t_0, bool t_1, bool t_2) {
    uint8_t word = BIT(7) | BIT(6);

    if (!count) word |= BIT(5);
    if (!status) word |= BIT(4);

    if (t_2) word |= BIT(3);
    if (t_1) word |= BIT(2);
    if (t_0) word |= BIT(1);

    return word;
}

/**
 * @brief   Decode init mode from a status byte.
 * @param   status     Raw status byte.
 * @param   initMode   Out: decoded init mode.
 * @return  RES_OK or error code.
 */
static inline Result timer_status_to_init_mode(TimerStatus status, TimerInitMode *initMode) {
    if (initMode == NULL) return RES_NULL_POINTER;

    switch (status & CTRL_LSB_MSB_MASK) {
    case CTRL_LSB    : *initMode = LSB; break;
    case CTRL_MSB    : *initMode = MSB; break;
    case CTRL_LSB_MSB: *initMode = LSB_MSB; break;
    default          : return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

/**
 * @brief   Decode counting mode from a status byte.
 * @param   status       Raw status byte.
 * @param   coutingMode  Out: decoded counting mode.
 * @return  RES_OK or error code.
 */
static inline Result timer_status_to_couting_mode(TimerStatus status, TimerCountingMode *coutingMode) {
    if (coutingMode == NULL) return RES_NULL_POINTER;

    switch (status & CTRL_MODE_MASK) {
    case CTRL_MODE_0: *coutingMode = MODE_0; break;
    case CTRL_MODE_1: *coutingMode = MODE_1; break;
    case CTRL_MODE_4: *coutingMode = MODE_4; break;
    case CTRL_MODE_5: *coutingMode = MODE_5; break;

    case CTRL_MODE_2:
    case CTRL_MODE_2_ALT: *coutingMode = MODE_2; break;

    case CTRL_MODE_3:
    case CTRL_MODE_3_ALT: *coutingMode = MODE_3; break;

    default: return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

/**
 * @brief   Decode BCD/binary mode from a status byte.
 * @param   status   Raw status byte.
 * @param   bcdMode  Out: decoded BCD mode.
 * @return  RES_OK or error code.
 */
static inline Result timer_status_to_bsc(TimerStatus status, TimerBCDMode *bcdMode) {
    if (bcdMode == NULL) return RES_NULL_POINTER;

    switch (status & CTRL_BCD_MASK) {
    case CTRL_BCD    : *bcdMode = BCD_MODE; break;
    case CTRL_NOT_BCD: *bcdMode = NOT_BCD_MODE; break;
    default          : return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

/**
 * @brief   Reads the current configuration (status byte) of a timer channel.
 * @param   timer   The timer channel to query (TIMER_0..TIMER_2).
 * @param   status  Out: pointer to where the returned status byte will be stored.
 * @return  RES_OK on success or an error code on failure.
 */
Result timer_get_conf_alt(Timer timer, TimerStatus *status);

/**
 * @brief   Displays a specific field of a timer’s status.
 * @param   timer   The timer channel (TIMER_0..TIMER_2).
 * @param   status  The status byte obtained via timer_get_conf_alt().
 * @param   field   Which field to display (tsf_all, tsf_initial, tsf_mode, tsf_base).
 * @return  RES_OK on success or an error code on failure.
 */
Result timer_display_conf_alt(Timer timer, TimerStatus status, enum timer_status_field field);

/**
 * @brief   Changes the operating frequency of a timer channel.
 * @param   timer  The timer channel to configure (TIMER_0..TIMER_2).
 * @param   freq   Desired timer operating frequency (Hz).
 * @return  RES_OK on success or an error code on failure.
 */
Result timer_set_frequency_alt(Timer timer, uint32_t freq);

#endif // _IO_TIMER_
