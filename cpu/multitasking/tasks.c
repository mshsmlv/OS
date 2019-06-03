#include "tasks.h"

extern stacks;


task task_list[10];
unsigned int tasks_num = 10;
unsigned int stack_size = 1024;
unsigned int current_task_index = -1;


void exit_handler() {
    while(1) {
        print("exit handler\n");
    };
}

void init_task(unsigned int func_address) {
    for(int i = 0; i < tasks_num; i++) {
        if(task_list[i].is_fineshed) {
            task_list[i].is_fineshed = 0;
            unsigned int new_stack_pointer = stacks + stack_size*(i + 1) - 4;
            *((unsigned int*)new_stack_pointer) = exit_handler;
            new_stack_pointer -= 4*5;
            task_list[i].ebp = new_stack_pointer;
            task_list[i].esp = new_stack_pointer;
            task_list[i].eip = func_address;
            task_list[i].index = i;

            task_list[i].edi = 0;
            task_list[i].esi = 0;
            task_list[i].ebx = 0;
            task_list[i].edx = 0;
            task_list[i].ecx = 0;
            task_list[i].eax = 0;
            print("init task with index: ");
            print_num(i);
            print("\n");
            print("init task with eip: ");
            print_num(task_list[i].eip);
            print("\n");
            print("init task with ret address: ");
            print_num((unsigned int)exit_handler);
            print("\n");
            print("init task with stack: ");
            print_num(new_stack_pointer);
            print("\n");
            return;
        }
    }
    print("Tasks limit exceeded\n");
}

void switch_task(stack_with_err_code* regs) {
    task_list[current_task_index].ebp = regs->ebp;
    task_list[current_task_index].esp = regs->esp;
    task_list[current_task_index].eip = regs->eip;

    task_list[current_task_index].edi = regs->edi;
    task_list[current_task_index].esi = regs->esi;
    task_list[current_task_index].ebx = regs->ebx;
    task_list[current_task_index].edx = regs->edx;
    task_list[current_task_index].ecx = regs->ecx;
    task_list[current_task_index].eax = regs->eax;

    task_list[current_task_index].eflags = regs->eflags;

    for (int i = current_task_index + 1; i < tasks_num; i++) {
        if (!task_list[i].is_fineshed) {
            regs->eip = task_list[i].eip;
            regs->esp = task_list[i].esp;
            regs->ebp = task_list[i].ebp;

            regs->edi = task_list[i].edi;
            regs->esi = task_list[i].esi;
            regs->ebx = task_list[i].ebx;
            regs->edx = task_list[i].edx;
            regs->ecx = task_list[i].ecx;
            regs->eax = task_list[i].eax;
//            regs->eflags = task_list[current_task_index].eflags;

            current_task_index = i;
            return;
        }
    }
    for (int i = 0; i <= current_task_index; i++) {
        if (!task_list[i].is_fineshed) {
            regs->eip = task_list[i].eip;
            regs->esp = task_list[i].esp;
            regs->ebp = task_list[i].ebp;

            regs->edi = task_list[i].edi;
            regs->esi = task_list[i].esi;
            regs->ebx = task_list[i].ebx;
            regs->edx = task_list[i].edx;
            regs->ecx = task_list[i].ecx;
            regs->eax = task_list[i].eax;

            current_task_index = i;
            return;
        }
    }
}


int custom_counter = 0;
void task1() {
    while(1) {
        if ((custom_counter % 1000000) == 0) { 
           print("Hello from task 1\n");
        }
        custom_counter++;
    }
}

void task2() {
    print("Hello from task 2\n");
}

void task3() {
    while(1) {
        //asm volatile("sti");
        if ((custom_counter % 1000000) == 0) {
            print("Hello from task 3\n");
        }
        custom_counter++;
    }
}

void task4() {
    while(1) {
      //  asm volatile("sti");
        if ((custom_counter % 1000000) == 0) {
           print("Hello from task 4\n");
        }
        custom_counter++;
    }
}

void start_multitasking() {
    for(int i = 0; i < tasks_num; i++) {
        task_list[i].is_fineshed = 1;
    }
    init_task((unsigned int)task1);
    init_task((unsigned int)task2);
    init_task((unsigned int)task3);
    init_task((unsigned int)task4);
    current_task_index = 0;
    task1();
}