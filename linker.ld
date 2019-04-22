OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)

SECTIONS
{
    . = 0x7e00;
	.text  .  : {
	    ./build/protect.o(.text) 
		*(EXCLUDE_FILE(./build/protect.o) .text)
    }
	.data : {
        *(.data)
	    *(.rodata)
    }
	.bss : {
        *(.bss)
    }
}
