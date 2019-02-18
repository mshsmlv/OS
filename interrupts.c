#include "print.c"

extern void idt_flush(unsigned int);
extern void isr0();
extern void isr1();
extern void isr2();

struct idt_entry_struct {
    unsigned short offset_1; // offset bits 0..15
    unsigned short sel; // Kernel segment selector.
    unsigned char zero; // unused, set to 0
    unsigned char type_attr; // type and attributes, see below
    unsigned short offset_2; // offset bits 16..31
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t; 

struct idt_ptr_struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

typedef struct registers {
   unsigned int ds;                  // Data segment selector
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   unsigned int int_no, err_code;    // Interrupt number and error code (if applicable)
   unsigned int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

static void init_idt() {
   idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
   idt_ptr.base  = (unsigned int)&idt_entries;

   idt_set_gate( 0, (unsigned int)isr0, 0x08, 0x8E);
   idt_set_gate( 1, (unsigned int)isr1, 0x08, 0x8E);
   idt_set_gate( 2, (unsigned int)isr2, 0x08, 0x8E);

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

void isr_handler(registers_t regs) {
   print("recieved interrupt: ");
   char int_no[10]; str(int_no, regs.int_no);
   print(int_no);
   print("\n");
}


