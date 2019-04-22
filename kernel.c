#include "interrupts.c"

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

void main() {
   init_idt();
   test_interrupts();
   init_timer();
   asm volatile ("sti");
}
