#include "KBC.h"
#include "../utils.h"

Result KBC_read_status(KBCStatus *status) {
    if (status == NULL) return RES_NULL_POINTER;

    KBCStatus temp_status;
    RETURN_IF_ERROR(util_sys_inb_alt(KBC_STATUS_REG, &temp_status));

    *status = temp_status;
    return RES_OK;
}

Result KBC_read_output(KBCOutput *output) {
    if (output == NULL) return RES_NULL_POINTER;

    KBCStatus status;
    RETURN_IF_ERROR(KBC_read_status(&status));
    if (!KBC_output_buffer_full(status)) return RES_NOT_READY;

    KBCOutput temp_output;
    RETURN_IF_ERROR(util_sys_inb_alt(KBC_OUT_BUFFER, &temp_output));

    *output = temp_output;
    return RES_OK;
}

Result KBC_write_command(KBCCommand command) {
    int tries = KBC_MAX_TRIES;

    while (tries) {
        KBCStatus status;
        RETURN_IF_ERROR(KBC_read_status(&status));

        // Write if the KBC is ready to receive input
        if (!KBC_input_buffer_full(status)) {
            RETURN_IF_ERROR(util_sys_outb(KBC_COMMAND_REG, command));
            return RES_OK;
        }

        // Wait before retrying
        tickdelay(micros_to_ticks(KBC_WAIT_DELAY));
    }

    // Timeout after enough tries
    return RES_TIMEOUT;
}

Result KBC_write_command_with_arg(KBCCommand command, KBCArgument argument) {
    // Write the command
    RETURN_IF_ERROR(KBC_write_command(command));

    // Write the argument
    int tries = KBC_MAX_TRIES;

    while (tries) {
        KBCStatus status;
        RETURN_IF_ERROR(KBC_read_status(&status));

        // Write if the KBC is ready to receive input
        if (!KBC_input_buffer_full(status)) {
            RETURN_IF_ERROR(util_sys_outb(KBC_ARGUMENT_REG, argument));
            return RES_OK;
        }

        // Wait before retrying
        tickdelay(micros_to_ticks(KBC_WAIT_DELAY));
    }

    // Timeout after enough tries
    return RES_TIMEOUT;
}

Result KBC_read_command_byte(KBCCommand *commandByte) {
    RETURN_IF_ERROR(KBC_write_command(KBC_READ_COMMAND_BYTE_COMMAND));

    KBCCommand temp_commandByte;
    RETURN_IF_ERROR(KBC_read_output(&temp_commandByte));

    *commandByte = temp_commandByte;
    return RES_OK;
}
