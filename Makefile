all: boot.asm
	dd if=/dev/zero of=disk.img bs=1M count=1
	nasm -fbin boot.asm
	dd if=boot of=disk.img bs=512 count=5 conv=notrunc
#	dd if=alice of=disk.img bs=512 count=1 seek=1 conv=notrunc

run: disk.img
	bochs -qf bochs.conf

clean:
	rm boot disk.img
