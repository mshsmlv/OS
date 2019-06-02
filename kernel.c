#include "cpu/interrupts/interrupts.h"
#include "cpu/multitasking/tasks.h"
#include "periphery/pic8259/pic8259.h"
#include "periphery/timer/timer.h"
#include "periphery/keyboard/keyboard.h"

void test_interrupts() {
   // int a = 12/0;
    asm volatile ("int $0");
}

void main() {
   init_idt();
   test_interrupts();
   init_pic8259();
   init_timer();
   init_keyboard();
   start_multitasking();
}
