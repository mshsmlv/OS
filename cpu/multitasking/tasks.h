typedef struct task_t{
    unsigned int esp;
    unsigned int is_fineshed;
} __attribute__((packed)) task; 

typedef struct _task_stack {
    unsigned int esp;
    unsigned int edi, esi, ebp, _esp, ebx, edx, ecx, eax; // Pushed by pusha.
    unsigned int eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
} task_stack;

void init_task(unsigned int func_address);
void switch_task(task_stack* regs);
void start_multitasking();

static inline  __attribute__((always_inline)) void disable_intr(void) {
    asm volatile("cli");
}

static inline  __attribute__((always_inline)) void enable_intr(void) {
    asm volatile("sti");
}
