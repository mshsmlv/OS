[BITS 16]

org 0x7e00
    
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    cli ; disable interrupts
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    mov ax, 0x23
    jmp CODE_SEG:_main

[bits 32]

_main:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x90000
    mov esp, ebp

    mov ah, 0x0d
    mov ecx, 0
    mov ebx, 0xb8496
_print:
    mov al, [msg + ecx]
    cmp al, 0
    je _end
    mov [ebx], ax
    add ecx, 1
    add ebx, 2
    jmp _print


_end: jmp _end

gdt:

gdt_null:
   dq 0

gdt_code:
    dw 0FFFFh ; first 16 bits - limit of segement
    ;Base efines the location of byte 0 of the segment within the 4-GByte
    ;linear address space.
    dw 0 ; base
    db 0 ; base

    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt
    dd gdt

CODE_SEG equ gdt_code - gdt
DATA_SEG equ gdt_data - gdt

msg: db "Booting at the Disco!!!", 0
len_msg equ $-msg

times (512 - ($-$$)) nop

