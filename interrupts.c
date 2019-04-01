#include "print.c"

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

extern void idt_flush(unsigned int);

struct idt_entry_struct {
    unsigned short offset_1;  // offset bits 0..15
    unsigned short sel;       // Kernel segment selector.
    unsigned char  zero;      // unused, set to 0
    unsigned char  type_attr; // type and attributes, see below
    unsigned short offset_2;  // offset bits 16..31
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t; 

struct idt_ptr_struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

typedef struct _stack_with_err_code {
   unsigned int ds;                                     // Data segment selector
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   unsigned int int_no, err_code;                       // Interrupt number and error code (if applicable)
   unsigned int eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
}  stack_with_err_code;

struct _stack_without_err_code {
   unsigned int ds;                                     // Data segment selector
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   unsigned int int_no;
   unsigned int eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
}  __attribute__((packed));
typedef struct _stack_without_err_code stack_without_err_code;

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (unsigned int)&idt_entries;

    idt_set_gate(0, (unsigned int)isr_without_err0, 0x08, 0x8E);
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

    idt_flush((unsigned int)&idt_ptr);
}

void idt_set_gate(unsigned char num, unsigned int offset, unsigned short sel, unsigned char flags) {
    idt_entries[num].offset_1 = offset & 0xFFFF;
    idt_entries[num].offset_2 = (offset >> 16) & 0xFFFF;

    idt_entries[num].sel = sel;
    idt_entries[num].zero = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].type_attr   = flags /* | 0x60 */;
}

void isr_handler_with_err(stack_with_err_code regs) {
    print("recieved interrupt with err code: ");
    char int_no[10];
    str(int_no, regs.int_no);
    print(int_no);
    print("\n");
}

void isr_handler_without_err(stack_without_err_code regs) {
    print("recieved interrupt without err code: ");
    char int_no[10];
    str(int_no, regs.int_no);
    print(int_no);
    print("\n");
}


