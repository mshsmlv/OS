#include "keyboard.h"

#include "../screen/print.h"
#include "../../cpu/interrupts/interrupts.h"
#include "../helpers/helpers.h"

char scancode_to_ascii[100] = "\xff`1234567890-=\xff\xffqwertyuiop[]\xff\xff\x61sdfghjkl;'\x0a\xff\xffzxcvbnm,./\xff\xff\xff\xff ";

void keyboard_callback(stack_with_err_code regs) {
    char letter;
    unsigned int scan_code = inb(0x60);
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

void init_keyboard() {
    set_irq_handler(33, keyboard_callback);
}
