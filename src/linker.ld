/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

/* The bootloader will start execution at this entry point */
ENTRY(_start)

SECTIONS {
	. = 2M;
	
	.text : BLOCK(4K) ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}	

	.rodata : BLOCK(4K) ALIGN(4K) {
		*(.data)
	}

	.bss : BLOCK(4K) ALIGN(4K) {
		*(COMMON)
		*(.bss)
	}
}
