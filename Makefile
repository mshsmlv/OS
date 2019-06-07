CFLAGS=-m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -c -g

all: disk.img

protect.o: 
	nasm -f elf ./cpu/boot/protect.asm -o ./build/protect.o

interrupts.o: ./cpu/interrupts/interrupts.asm
	nasm -f elf ./cpu/interrupts/interrupts.asm -o ./build/interrupts.o

interrupts_c.o: ./cpu/interrupts/interrupts.c
	gcc $(CFLAGS) ./cpu/interrupts/interrupts.c -o ./build/interrupts_c.o -Iperiphery/helpers -Iperiphery/screen

pic8259.o: ./periphery/pic8259/pic8259.c
	gcc $(CFLAGS) ./periphery/pic8259/pic8259.c -o ./build/pic8259.o -Iperiphery/helpers

timer.o: ./periphery/timer/timer.c
	gcc $(CFLAGS) ./periphery/timer/timer.c -o ./build/timer.o -Iperiphery/helpers -Icpu/interrupts -Iperiphery/screen

keyboard.o: ./periphery/keyboard/keyboard.c
	gcc $(CFLAGS) ./periphery/keyboard/keyboard.c -o ./build/keyboard.o -Iperiphery/helpers -Iperiphery/screen -Icpu/interrupts

print.o: ./periphery/screen/print.c
	gcc $(CFLAGS) ./periphery/screen/print.c -o ./build/print.o -Iperiphery/helpers

tasks_c.o: ./cpu/multitasking/tasks.c
	gcc $(CFLAGS) ./cpu/multitasking/tasks.c -o ./build/tasks_c.o -Iperiphery/helpers -Icpu/interrupts

kernel.o: kernel.c
	gcc $(CFLAGS) kernel.c -o ./build/kernel.o -Iperiphery/pic8259 \
	 -Iperiphery/timer -Iperiphery/keyboard \
	 -Icpu/interrupts -Icpu/multitasking \

boot: ./cpu/boot/boot.asm
	nasm -fbin ./cpu/boot/boot.asm -o ./build/boot

kernel: protect.o kernel.o print.o interrupts_c.o interrupts.o pic8259.o timer.o keyboard.o tasks_c.o
	ld -T linker.ld ./build/*.o -o ./build/kernel

disk.img: boot kernel
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=./build/boot of=disk.img bs=512 count=4 conv=notrunc
	dd if=./build/kernel of=disk.img bs=512 count=100 seek=4 conv=notrunc

run: disk.img
	bochs -qf bochs.conf

clean:
	rm -f boot disk.img ./build/*

