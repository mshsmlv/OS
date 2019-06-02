#include "keyboard.h"

#include "../screen/print.h"
#include "../../cpu/interrupts/interrupts.h"
#include "../helpers/helpers.h"

char scancode_to_ascii[100] = "\xff`1234567890-=\xff\xffqwertyuiop[]\xff\xff\x61sdfghjkl;'\x0a\xff\xffzxcvbnm,./\xff\xff\xff\xff ";

void keyboard_callback(stack_with_err_code regs) {
    unsigned int status = read_byte_from_port(0x64);
    // Check read enable from -x60 port
    // and that ps/2 connector is clear.
    // If ps/2 connector is set, it means that
    // in the port 0x60 mouse data.
    if ((status & 0x1) && !(status & 0x20)) {
        char letter;
        unsigned int scan_code = read_byte_from_port(0x60);
        io_wait();
        if(scan_code < 59) {
            if (scan_code == 28) {
                print("\n");
                return;
            }
            letter = scancode_to_ascii[scan_code];
            if (letter != 0xff) {
                print_char(letter);
            }
        }
    }
}

void init_keyboard() {
    set_irq_handler(33, keyboard_callback);

    char imr;
    imr = read_byte_from_port(0x21);
    io_wait();
    imr = imr & (0xff - 2); // enable keyboard interrupt (pin 1)
    send_byte_to_port(0x21, imr);
    io_wait();

}
