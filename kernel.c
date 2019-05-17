#include "cpu/interrupts/interrupts.h"
#include "periphery/pic8259/pic8259.h"
#include "periphery/timer/timer.h"
#include "periphery/keyboard/keyboard.h"

extern int test();


void test_interrupts() {
   // int a = 12/0;
    asm volatile ("int $0");
}

void main() {
   init_idt();
   //test();
   test_interrupts();
   init_pic8259();
   init_timer();
   init_keyboard();
}
