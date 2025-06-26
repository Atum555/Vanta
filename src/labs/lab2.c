#include "../drivers/timer/timer.h"
#include "../utils/result.h"
#include <lcom/lab2.h>
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    lcf_start(argc, argv);

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
    TimerStatus status;
    RETURN_IF_ERROR(timer_get_conf_alt(timer, &status));
    RETURN_IF_ERROR(timer_display_conf_alt(timer, status, field));
    return RES_OK;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
    /* To be implemented by the students */
    printf("%s is not yet implemented!\n", __func__);

    return 1;
}

int(timer_test_int)(uint8_t time) {
    /* To be implemented by the students */
    printf("%s is not yet implemented!\n", __func__);

    return 1;
}
