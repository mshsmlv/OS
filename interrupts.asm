[global idt_flush]
[extern isr_handler_without_err]
[extern isr_handler_with_err]

idt_flush:
    mov eax, [esp+4]   
    lidt [eax]
    ret

%macro ISR_WITHOUT_ERR 1
    [global isr_without_err%1]
    isr_without_err%1:
        push byte %1    
        jmp isr_handle_without_err
%endmacro

%macro ISR_WITH_ERR 1
    [global isr_with_err%1]
    isr_with_err%1:
        push byte 0       
        push byte %1     
        jmp isr_handle_with_err
%endmacro

    ISR_WITHOUT_ERR 0
    ISR_WITHOUT_ERR 1
    ISR_WITHOUT_ERR 2
    ISR_WITHOUT_ERR 3
    ISR_WITHOUT_ERR 4
    ISR_WITHOUT_ERR 5
    ISR_WITHOUT_ERR 6
    ISR_WITHOUT_ERR 7
    ISR_WITH_ERR 8
    ISR_WITHOUT_ERR 9
    ISR_WITH_ERR 10
    ISR_WITH_ERR 11
    ISR_WITH_ERR 12
    ISR_WITH_ERR 13
    ISR_WITH_ERR 14
    ISR_WITHOUT_ERR 15
    ISR_WITHOUT_ERR 16
    ISR_WITHOUT_ERR 17
    ISR_WITHOUT_ERR 18
    ISR_WITHOUT_ERR 19
    ISR_WITHOUT_ERR 20
    ISR_WITHOUT_ERR 21
    ISR_WITHOUT_ERR 22
    ISR_WITHOUT_ERR 23
    ISR_WITHOUT_ERR 24
    ISR_WITHOUT_ERR 25
    ISR_WITHOUT_ERR 26
    ISR_WITHOUT_ERR 27
    ISR_WITHOUT_ERR 28
    ISR_WITHOUT_ERR 29
    ISR_WITHOUT_ERR 30
    ISR_WITHOUT_ERR 31

isr_handle_with_err:
    pushad                   ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax

    call isr_handler_with_err

    pop eax        ; reload the original data segment descriptor
    mov ds, ax

    popad          ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

isr_handle_without_err:
    pushad

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    
    call isr_handler_without_err

    pop eax
    mov ds, ax

    popad
    add esp, 4
    iret

