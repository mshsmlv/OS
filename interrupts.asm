[global idt_flush]
[extern isr_handler]

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter. 
    lidt [eax]        ; Load the IDT pointer.
    ret

%macro ISR 1
    [global isr%1]
    isr%1:
        cli                 ; Disable interrupts
        push byte 0         ; Push a dummy error code (if ISR0 doesn't push it's own error code)
        push byte %1        ; Push the interrupt number (0)
        jmp isr_common_stub ; Go to our common handler.
%endmacro

    ISR 0
    ISR 1
    ISR 2
    ISR 3
    ISR 4
    ISR 5
    ISR 6
    ISR 7
    ISR 8
    ISR 9
    ISR 10
    ISR 11
    ISR 12
    ISR 13
    ISR 14
    ISR 15
    ISR 16
    ISR 17
    ISR 18
    ISR 19
    ISR 20
    ISR 21
    ISR 22
    ISR 23
    ISR 24
    ISR 25
    ISR 26
    ISR 27
    ISR 28
    ISR 29
    ISR 30
    ISR 31

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

