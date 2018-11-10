OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)

SECTIONS
{
    . = 0x7e00;
	.text  .  : {
	    protect.o(.text) 
		*(EXCLUDE_FILE(protect.o) .text)
    }
	.data : {
        *(.data)
	    *(.rodata)
    }
	.bss : {
        *(.bss)
    }
}
