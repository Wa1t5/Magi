/* The bootloader will start execution at this entry point */
ENTRY(_start)

SECTIONS {
	. = 2M;
	
	.text : ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}	

	.rodata : ALIGN(4K) {
		*(.data)
	}

	.bss : ALIGN(4K) {
		*(COMMON)
		*(.bss)
	}
}
