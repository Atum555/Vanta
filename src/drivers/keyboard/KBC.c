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
