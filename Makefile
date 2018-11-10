all: boot.asm
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin boot.asm
#	nasm -fbin protect.asm
	nasm -f elf protect.asm -o protect.o
	gcc -m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -c kernel.c
	ld -T linker.ld protect.o kernel.o
	dd if=boot of=disk.img bs=512 count=4 conv=notrunc
	dd if=a.out of=disk.img bs=512 count=1 seek=4 conv=notrunc

run: disk.img
	bochs -qf bochs.conf

clean:
	rm boot disk.img
