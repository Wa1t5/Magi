; Constants for multiboot header 
MBALIGN    equ 1<<0                 ; Align our modules with the page boundaries
MBMEMINFO  equ 1<<1               ; Provide memory map for our modules
MBFLAGS    equ MBALIGN | MBMEMINFO      ; List our flags
MBMAGIC    equ 0x1BADB002           ; Magic number to let the bootloader find the multiboot header
MBCHECKSUM equ -(MBMAGIC + MBFLAGS)  ; Checksum of our header, the '-' operator triggers an binary inversion

; Multiboot header
section .multiboot
align 4         ; Specify that we want an 4bit alignment
        dd MBMAGIC ;Create int variables for our constants
        dd MBFLAGS
        dd MBCHECKSUM

; Declare our kernel stack, x86 stacks grows from top to bottom 
section .bss  ; Declare our stack on section .bsss because this is the section for uninitialized code
              ; and we don't want our kernel to include an initialized empty stack because it takes
              ; memory
        
align 16      ; Specify that we want an alignment of 16bit
stack_bottom:
resb 16384    ; Skip 16Kib
stack_top:

; Kernel entry point
section .text                                 ; Specify to the compiler that it needs to translate this part of the code to machine
                                              ; code, because the .text section is used to write more human-readable code
global _start:function (_start.end - _start) ; Make our kernel entry acessible to the entire code and mark it as a funciton
_start:
        ; Make the stack pointer register(esp) point to the top of our stack 
        mov esp, stack_top

        ; Execute kernel_main
        extern kernel_main
        call kernel_main

        ; Put the computer into an infinity loop waiting for halt
        cli
.hang:  hlt
        jmp .hang

.end:
