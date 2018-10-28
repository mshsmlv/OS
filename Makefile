all: boot.asm
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin boot.asm
	nasm -fbin protect.asm
	dd if=boot of=disk.img bs=512 count=4 conv=notrunc
	dd if=protect of=disk.img bs=512 count=1 seek=4 conv=notrunc

run: disk.img
	bochs -qf bochs.conf

clean:
	rm boot disk.img
