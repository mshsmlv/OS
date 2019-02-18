[BITS 16]

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
    jmp CODE_SEG:_main

[bits 32]
[extern main]

_main:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

_end:
    call main 
    jmp $

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

