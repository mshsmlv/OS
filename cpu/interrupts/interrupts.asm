[global idt_flush]
[global irq_timer_handler]

[extern isr_handler_without_err]
[extern common_handler]
[extern irq_common_handler]
[extern timer_callback]

idt_flush:
    mov eax, [esp+4]   
    lidt [eax]
    sti
    ret

%macro ISR_WITHOUT_ERR 1
    [global isr_without_err%1]
    isr_without_err%1:
        push 0
        push byte %1    
        jmp isr_common_handle
%endmacro

%macro ISR_WITH_ERR 1
    [global isr_with_err%1]
    isr_with_err%1:
        push byte %1     
        jmp isr_common_handle
%endmacro

%macro IRQ 1
    [global irq%1]
    irq%1:
        push byte 0
        push byte %1
        jmp irq_handle
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
    IRQ 33
    IRQ 34
    IRQ 35
    IRQ 36
    IRQ 37
    IRQ 38
    IRQ 39
    IRQ 40
    IRQ 41
    IRQ 42
    IRQ 43
    IRQ 44
    IRQ 45
    IRQ 46
    IRQ 47

isr_common_handle:
    pushad                   ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax

    call common_handler

    pop eax        ; reload the original data segment descriptor
    mov ds, ax

    popad          ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

irq_handle:
    pushad

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    
    call irq_common_handler

    pop eax
    mov ds, ax

    popad
    add esp, 8
    iret

irq_timer_handler:
    cli
    push 0
    push 32

    pushad

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax

    call irq_common_handler
     
    pop eax
    mov ds, ax
 
    ;edi, esi, ebp, esp, ebx, edx, ecx, eax

    pop edi
    pop esi
    pop ebp

    mov ebx, esp ; store old esp

    pop esp ; store esp

    mov eax, [ebx + 28] ; eip
    mov [esp + 8], eax

    mov eax, [ebx + 32] ; cs
    mov [esp + 12], eax

    mov eax, [ebx + 36] ; eflags
    
    mov [esp + 16], eax

    mov eax, [ebx + 36]
    mov eax, [esp + 16]

    mov eax, [ebx + 16] ; eax
    push eax

    mov eax, [ebx + 12] ; ecx
    push eax

    mov eax, [ebx + 8] ; edx
    push eax

    mov eax, [ebx + 4] ; ebx
    push eax

    pop ebx
    pop edx
    pop ecx
    pop eax

    add esp, 8
    sti
    iret

