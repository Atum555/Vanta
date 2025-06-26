#include "timer.h"

Result timer_get_conf_alt(Timer timer, TimerStatus *status) {
    if (status == NULL) return RES_NULL_POINTER;

    TimerCtrlWord command = timer_readback_command(false, true, timer == TIMER_0, timer == TIMER_1, timer == TIMER_2);
    RETURN_IF_ERROR(util_sys_outb(TIMER_CTRL_REG, command));

    TimerStatus temp_status;
    RETURN_IF_ERROR(util_sys_inb_alt(timer_to_reg(timer), &temp_status));
    *status = temp_status;

    return RES_OK;
}

Result timer_display_conf_alt(Timer timer, TimerStatus status, enum timer_status_field field) {
    union timer_status_field_val value;

    TimerInitMode     initMode;
    TimerCountingMode coutingMode;
    TimerBCDMode      bcdMode;

    switch (field) {
    case tsf_all: value.byte = status; break;

    case tsf_initial:
        if (IS_ERROR(timer_status_to_init_mode(status, &initMode))) {
            value.in_mode = INVAL_val;
            break;
        }

        switch (initMode) {
        case LSB    : value.in_mode = LSB_only; break;
        case MSB    : value.in_mode = MSB_only; break;
        case LSB_MSB: value.in_mode = MSB_after_LSB; break;
        default     : return RES_ERROR;
        }
        break;

    case tsf_mode:
        RETURN_IF_ERROR(timer_status_to_couting_mode(status, &coutingMode));
        value.count_mode = coutingMode;
        break;

    case tsf_base:
        RETURN_IF_ERROR(timer_status_to_bsc(status, &bcdMode));
        value.bcd = bcdMode;
        break;

    default: return RES_INVALID_ARGUMENT;
    }

    if (IS_ERROR(timer_print_config(timer, field, value))) return RES_ERROR;
    return RES_OK;
}

Result timer_set_frequency_alt(Timer timer, uint32_t freq) {
    // Calculate counter value for the given frequency
    if (freq < 19 || freq > TIMER_FREQUENCY) return RES_INVALID_ARGUMENT;
    uint16_t counterValue = TIMER_FREQUENCY / freq;

    // Get counter initial value as separate bytes
    uint8_t counterValueMSB, counterValueLSB;
    RETURN_IF_ERROR(util_get_MSB_alt(counterValue, &counterValueMSB));
    RETURN_IF_ERROR(util_get_LSB_alt(counterValue, &counterValueLSB));

    // Read timer current status
    TimerStatus status;
    RETURN_IF_ERROR(timer_get_conf_alt(timer, &status));

    // Store current state not to lose
    TimerCountingMode countingMode;
    TimerBCDMode      bcdMode;
    RETURN_IF_ERROR(timer_status_to_couting_mode(status, &countingMode));
    RETURN_IF_ERROR(timer_status_to_bsc(status, &bcdMode));

    // Create new control word
    TimerCtrlWord word;
    RETURN_IF_ERROR(timer_ctrl_word(timer, LSB_MSB, countingMode, bcdMode, &word));

    //! Hack to give what is expected to LCOM
    // Some options for the TimerCountingMode have multiple different 
    // representations even though it should always be only one
    // this code keeps the representation stored on the register
    if (status & BIT(3)) word |= BIT(3);

    // Update counter with new control word
    RETURN_IF_ERROR(util_sys_outb(TIMER_CTRL_REG, word));

    // Write counter initial bytes to timer
    RETURN_IF_ERROR(util_sys_outb(timer_to_reg(timer), counterValueLSB));
    RETURN_IF_ERROR(util_sys_outb(timer_to_reg(timer), counterValueMSB));

    return RES_OK;
}
