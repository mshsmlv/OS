CFLAGS=-m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -c 

all: run

protect.o: protect.asm
	nasm -f elf protect.asm -o protect.o

interrupts.o: interrupts.asm
	nasm -f elf interrupts.asm -o interrupts.o

kernel.o: kernel.c
	gcc $(CFLAGS) kernel.c

boot: boot.asm
	nasm -fbin boot.asm

kernel: protect.o kernel.o interrupts.o linker.ld
	ld -T linker.ld protect.o kernel.o interrupts.o -o kernel

disk.img: boot kernel
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=boot of=disk.img bs=512 count=4 conv=notrunc
	dd if=kernel of=disk.img bs=512 count=8 seek=4 conv=notrunc

run: disk.img
	bochs -qf bochs.conf

clean:
	rm boot disk.img *.o

