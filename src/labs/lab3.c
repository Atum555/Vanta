#include "../drivers/keyboard/KBC.h"
#include "../drivers/keyboard/keyboard.h"
#include "../utils/result.h"
#include <lcom/lab3.h>
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab3/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv)) return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int(kbd_test_scan)() {
    uint8_t keyboard_irq_bit;
    RETURN_IF_ERROR(keyboard_subscribe_int(&keyboard_irq_bit));

    // Keyboard variables
    uint16_t scancode = 0x00;

    // Main interrupt loop
    int     ipc_status;
    message msg;
    int     r;
    while (scancode != 0x81) {
        // Get a request message.
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {                               // Check received notification
            switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:                                             // Check it is a hardware interrupt notification
                if (msg.m_notify.interrupts & BIT(keyboard_irq_bit)) { // Check interrupt bit
                    if (IS_OK(keyboard_ih(&scancode))) {
                        // Split scancode into 2 bytes
                        uint8_t buf[2] = {
                            (uint8_t)((scancode >> 8) & 0xFF),
                            (uint8_t)(scancode & 0xFF),
                        };

                        // Send scancode in the proper format to the printing function
                        kbd_print_scancode(!(buf[1] & BIT(7)), buf[0] == 0 ? 1 : 2, buf[0] == 0 ? &buf[1] : buf);
                    }
                }
            default: break;
            }
        }
    }

    // Unsubscribe from KBC before returning
    RETURN_IF_ERROR(keyboard_unsubscribe_int());
    return RES_OK;
}

int(kbd_test_poll)() {
    /* To be completed by the students */
    printf("%s is not yet implemented!\n", __func__);

    return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
    /* To be completed by the students */
    printf("%s is not yet implemented!\n", __func__);

    return 1;
}
