/*/
 * Author: Waltz (Wa1t5)
 * Project: Neon Genesis
/*/

/* Constants for multiboot header */
.set ALIGN, 1<<0                    // Align our modules with the page boundaries
.set MEMINFO, 1<<1                  // Provide memory map for our modules
.set FLAGS, ALIGN | MEMINFO         // List our flags
.set MAGIC, 0x1BADB002              // Magic number to let the bootloader find the multiboot header
.set CHECKSUM, -(MAGIC + FLAGS)     // Checksum of our header, the '-' operator triggers an binary inversion

/* Multiboot header */
.section .multiboot
.align 4         // Specify that we want an 4bit alignment
.long MAGIC      //Create int variables for our constants
.long FLAGS
.long CHECKSUM

/* Declare our kernel stack, x86 stacks grows from top to bottom  */
.section .bss  // Declare our stack on section .bsss because this is the section for uninitialized code
               // and we don't want our kernel to include an initialized empty stack because it takes
               // memory
        
.align 16      // Specify that we want an alignment of 16bit
stack_bottom:
.skip 16384    // Skip 16Kib
stack_top:

/* Kernel entry point */
.section .text                                 // Specify to the compiler that it needs to translate this part of the code to machine
                                                // code, because the .text section is used to write more human-readable code

/* Make our kernel entry acessible to the entire code and mark it as a funciton */
.type _start, @function
.global _start
_start:
        /* Make the stack pointer register(esp) point to the top of our stack */
        mov $stack_top, %esp

        /* Execute first impact */
        .extern first_impact
        call first_impact

        /* Put the computer into an infinity loop waiting for halt */
        cli
1:      hlt
        jmp 1
