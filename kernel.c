#include "interrupts.c"

void main() {
    init_idt();
    asm volatile ("int $0x0");
    asm volatile ("int $0x1");
    asm volatile ("int $0x2");
}


