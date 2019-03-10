#include "interrupts.c"

void main() {
    init_idt();
    asm volatile ("int $32");
}


