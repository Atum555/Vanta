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
    RETURN_IF_ERROR(timer_set_frequency_alt(timer, freq));
    return RES_OK;
}

int(timer_test_int)(uint8_t time) {
    // Subscribe to timer interrupts
    uint8_t timer_irq_bit;
    RETURN_IF_ERROR(timer_subscribe_int_alt(&timer_irq_bit));

    // Timer counter
    uint32_t timer_counter = 0;

    // Main interrupt loop
    int     ipc_status;
    message msg;
    int     r;
    while (time) {
        // Get a request message.
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {                            // Check received notification
            switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:                                          // Check it is a hardware interrupt notification
                if (msg.m_notify.interrupts & BIT(timer_irq_bit)) { // Check interrupt bit
                    // Increment counter
                    timer_counter++;

                    // If a minute has passed
                    // Decrement time
                    // Print time passed
                    if (timer_counter >= 60) {
                        timer_counter = 0;
                        time--;
                        timer_print_elapsed_time();
                    }
                }
                break;
            default: break;
            }
        }
    }

    // Unsubscribe from timer before returning
    RETURN_IF_ERROR(timer_unsubscribe_int_alt());
    return RES_OK;
}
