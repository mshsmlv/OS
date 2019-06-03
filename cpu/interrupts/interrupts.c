#include "interrupts.h"

#include "../../periphery/screen/print.h"
#include "../../periphery/helpers/helpers.h"

extern void isr_without_err0();
extern void isr_without_err1();
extern void isr_without_err2();
extern void isr_without_err3();
extern void isr_without_err4();
extern void isr_without_err5();
extern void isr_without_err6();
extern void isr_without_err7();
extern void isr_with_err8();
extern void isr_without_err9();
extern void isr_with_err10();
extern void isr_with_err11();
extern void isr_with_err12();
extern void isr_with_err13();
extern void isr_with_err14();
extern void isr_without_err15();
extern void isr_without_err16();
extern void isr_without_err17();
extern void isr_without_err18();
extern void isr_without_err19();
extern void isr_without_err20();
extern void isr_without_err21();
extern void isr_without_err22();
extern void isr_without_err23();
extern void isr_without_err24();
extern void isr_without_err25();
extern void isr_without_err26();
extern void isr_without_err27();
extern void isr_without_err28();
extern void isr_without_err29();
extern void isr_without_err30();
extern void isr_without_err31();
extern void irq_timer_handler();
extern void irq33();
extern void irq34();
extern void irq35();
extern void irq36();
extern void irq37();
extern void irq38();
extern void irq39();
extern void irq40();
extern void irq41();
extern void irq42();
extern void irq43();
extern void irq44();
extern void irq45();
extern void irq46();
extern void irq47();

extern void idt_flush(unsigned int);

void set_irq_handler(int index, irq_handler func) {
    irq_handlers[index] = func;
}

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void idt_set_gate(unsigned char num, unsigned int offset, unsigned short sel, unsigned char flags) {
    idt_entries[num].offset_1 = offset & 0xFFFF;
    idt_entries[num].offset_2 = (offset >> 16) & 0xFFFF;

    idt_entries[num].sel = sel;
    idt_entries[num].zero = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].type_attr   = flags /* | 0x60 */;
}

void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 48 -1;
    idt_ptr.base  = (unsigned int)&idt_entries;

    idt_set_gate(0, (unsigned int)isr_without_err0, 0x08, 0x8E); //(10001110) {p}{DPL} 11{size of gate 32 bit}0
    idt_set_gate(1, (unsigned int)isr_without_err1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned int)isr_without_err2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned int)isr_without_err3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned int)isr_without_err4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned int)isr_without_err5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned int)isr_without_err6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned int)isr_without_err7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned int)isr_with_err8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned int)isr_without_err9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned int)isr_with_err10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned int)isr_with_err11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned int)isr_with_err12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned int)isr_with_err13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned int)isr_with_err14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned int)isr_without_err15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned int)isr_without_err16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned int)isr_without_err17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned int)isr_without_err18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned int)isr_without_err19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned int)isr_without_err20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned int)isr_without_err21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned int)isr_without_err22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned int)isr_without_err23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned int)isr_without_err24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned int)isr_without_err25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned int)isr_without_err26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned int)isr_without_err27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned int)isr_without_err28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned int)isr_without_err29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned int)isr_without_err30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned int)isr_without_err31, 0x08, 0x8E);
    idt_set_gate(32, (unsigned int)irq_timer_handler, 0x08, 0x8E);
    idt_set_gate(33, (unsigned int)irq33, 0x08, 0x8E);
    idt_set_gate(34, (unsigned int)irq34, 0x08, 0x8E);
    idt_set_gate(35, (unsigned int)irq35, 0x08, 0x8E);
    idt_set_gate(36, (unsigned int)irq36, 0x08, 0x8E);
    idt_set_gate(37, (unsigned int)irq37, 0x08, 0x8E);
    idt_set_gate(38, (unsigned int)irq38, 0x08, 0x8E);
    idt_set_gate(39, (unsigned int)irq39, 0x08, 0x8E);
    idt_set_gate(40, (unsigned int)irq40, 0x08, 0x8E);
    idt_set_gate(41, (unsigned int)irq41, 0x08, 0x8E);
    idt_set_gate(42, (unsigned int)irq42, 0x08, 0x8E);
    idt_set_gate(43, (unsigned int)irq43, 0x08, 0x8E);
    idt_set_gate(44, (unsigned int)irq44, 0x08, 0x8E);
    idt_set_gate(45, (unsigned int)irq45, 0x08, 0x8E);
    idt_set_gate(46, (unsigned int)irq46, 0x08, 0x8E);
    idt_set_gate(47, (unsigned int)irq47, 0x08, 0x8E);

    print("irq timer handler: \n");
    print_num((unsigned int)irq_timer_handler);
    print("\n");

    for(int i = 0; i < 256; i++) {
        irq_handlers[i] = 0;
    }

    idt_flush((unsigned int)&idt_ptr);
}

void common_handler(stack_with_err_code regs) {
    // print("recieved interrupt with err code: ");
    // char int_no[10];
    // str(int_no, regs.int_no);
    // print(int_no);
    // print("\n");
}

void irq_common_handler(stack_with_err_code regs) {
    irq_handler handler = irq_handlers[regs.int_no];
    if (handler != 0) {
        // print("handler address: ");
        // print_num((unsigned int)handler);
        // print("\n");
        // print("cs :");
        // print_num(regs.cs);
        // print("\n");
        // print("eip: ");
        // print_num(regs.eip);
        // print("\n");
        (*handler)(&regs);      
    }
    if (regs.int_no >= 40) send_byte_to_port(0xa0, 0x20); /* slave */
    send_byte_to_port(0x20, 0x20); /* master */
}
int tick1 = 0;
void irq_timer_handler_c(task_stack stack_context) {
     if (tick1 == 1000) {
        tick1 = 0;
        print("-------------------------\n");
        print("regs.eflags: ");
        print_num(stack_context.eflags);
        print("\n");
        switch_task(&stack_context);
    }
    tick1++;
    send_byte_to_port(0x20, 0x20); /* master */
}
