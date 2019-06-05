#include "interrupts.h"
#include "tasks.h"
#include "pic8259.h"
#include "timer.h"
#include "keyboard.h"

void test_interrupts() {
   // int a = 12/0;
    asm volatile ("int $0");
}

void main() {
   init_idt();
  // test_interrupts();
   init_pic8259();
   init_timer();
   init_keyboard();
   start_multitasking();
}
