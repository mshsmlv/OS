[BITS 16]

org 0x7c00

mov ax, 0
mov ss, ax
mov ds, ax
mov es, ax

jmp 0x0:_init

_init:
mov ax, 0xb800
mov es, ax
xor bx, bx

_fill_by_spaces:
    cmp bx, 80 * 25 * 2
    je _main
    mov [es:bx], word 0x0720
    add bx, 2
    jmp _fill_by_spaces
    
_main:
    mov si, 2

_print_art:
    cmp si, 5
    je _end
    mov ax, 0x0
    mov es, ax
    mov bx,0x0500 ; [es:bp] -> buffer

    mov ah, 0x2
    mov al, 1  ; number of sectors
    mov cx, si ; sector number
    mov dh, 0  ; head number
    mov dl, 0x80 ; drive number (bit 7 set for hard disk)
    int 13h

    mov ax, 0
    mov es, ax
    mov ah, 13h
    mov al, 1
    mov bh, 1 ; page
    mov bl, 0x0d
    mov bp, 0x0500 ; [es:bp] -> string to write
    mov cx, 7
    mov dx, si
    add dx, 8
    shl dx, 8 ; dh - raw
    mov dl, 35 ; dl - column
    int 10h
    add si, 1
    jmp _print_art

_end:
    mov ah, 0x2
    mov bh, 0
    mov dh, 26
    mov dl, 0
    int 10h

    mov ax, 0x0
    mov es, ax
    mov bx,0x7e00 ; [es:bp] -> buffer

    mov ah, 0x2
    mov al, 50  ; number of sectors
    mov cx, 5 ; sector number
    mov dh, 0  ; head number
    mov dl, 0x80 ; drive number (bit 7 set for hard disk)
    int 13h
    jmp 0:0x7e00

times (510 - ($-$$)) nop

dw 0xaa55
db " /\_/\ "
times 505 db 0xaa ; fill 2nd sector with 0xaa
db "( o.o )"
times 505 db 0xaa ; fill 3nd sector with 0xaa
db " > ^ < "
times 505 db 0xaa ; fill 4nd sector with 0xaa

