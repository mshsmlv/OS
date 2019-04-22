#include "cpu/interrupts/interrupts.h"
#include "periphery/pic8259/pic8259.h"
#include "periphery/timer/timer.h"


void test_interrupts() {
   // int a = 12/0;
    asm volatile ("int $0");
    asm volatile ("int $0");
    asm volatile ("int $1");
    asm volatile ("int $2");
    asm volatile ("int $3");
    asm volatile ("int $4");
    asm volatile ("int $5");
    asm volatile ("int $6");
    asm volatile ("int $7");
    asm volatile ("int $8");
    asm volatile ("int $9");
    asm volatile ("int $10");
    asm volatile ("int $11");
    asm volatile ("int $12");
    asm volatile ("int $13");
    asm volatile ("int $14");
    asm volatile ("int $15");
    asm volatile ("int $16");
    asm volatile ("int $17");
    asm volatile ("int $18");
    asm volatile ("int $19");
    asm volatile ("int $20");
    asm volatile ("int $21");
    asm volatile ("int $22");
    asm volatile ("int $23");
    asm volatile ("int $24");
    asm volatile ("int $25");
    asm volatile ("int $26");
    asm volatile ("int $27");
    asm volatile ("int $28");
    asm volatile ("int $29");
    asm volatile ("int $30");
    asm volatile ("int $31");
}

void main() {
   init_idt();
   test_interrupts();
   init_pic8259();
   init_timer();
}
