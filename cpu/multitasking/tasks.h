#pragma once
#include "interrupts.h"

typedef struct task_t{
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int eip, eflags;
    unsigned int is_fineshed;
} __attribute__((packed)) task; 

void init_task(unsigned int func_address);
void scheduler();
void switch_task(task_stack* regs);
void start_multitasking();

static inline void disable_intr(void) {
    asm volatile("cli");
}

static inline void enable_intr(void) {
    asm volatile("sti");
}
