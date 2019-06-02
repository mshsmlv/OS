#pragma once
#include "../interrupts/interrupts.h"

typedef struct task_t{
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int eip, eflags;
    unsigned int index;
    unsigned int is_fineshed;
} __attribute__((packed)) task; 

void init_task(unsigned int func_address);
void scheduler();
void switch_task(stack_with_err_code* regs);
void start_multitasking();

