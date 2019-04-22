#include "timer.h"

#include "../../cpu/interrupts/interrupts.h"
#include "../helpers/helpers.h"
#include "../screen/print.h"

int tick = 0;

static void timer_callback(stack_with_err_code regs) {
    tick++;
    if (regs.int_no >= 40) send_byte_to_port(0xa0, 0x20); /* slave */
    send_byte_to_port(0x20, 0x20); /* master */
    if (tick == 1000) {
        tick = 0;
        print("tick\n");
    }
}

void init_timer() {
    set_irq_handler(32, timer_callback);
    /* Get the PIT value: hardware clock at 1193180 Hz */
    unsigned int divisor = 1193180;
    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)((divisor >> 8) & 0xFF);
    /* Send the command */
    send_byte_to_port(0x43, 0x36); /* Command port */
    send_byte_to_port(0x40, low);
    send_byte_to_port(0x40, high);
    print("timer on\n");
}
