[global idt_flush]
[global isr0]
[global isr1]
[global isr2]
[extern isr_handler]

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter. 
    lidt [eax]        ; Load the IDT pointer.
    ret

isr0:
    cli                 ; Disable interrupts
    push byte 0         ; Push a dummy error code (if ISR0 doesn't push it's own error code)
    push byte 0         ; Push the interrupt number (0)
    jmp isr_common_stub ; Go to our common handler.

isr1:
    cli                 ; Disable interrupts
    push byte 0         ; Push a dummy error code (if ISR0 doesn't push it's own error code)
    push byte 1         ; Push the interrupt number (0)
    jmp isr_common_stub ; Go to our common handler.

isr2:
    cli                 ; Disable interrupts
    push byte 0         ; Push a dummy error code (if ISR0 doesn't push it's own error code)
    push byte 2         ; Push the interrupt number (0)
    jmp isr_common_stub ; Go to our common handler.

isr_common_stub:
    pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax        ; reload the original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                     ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

