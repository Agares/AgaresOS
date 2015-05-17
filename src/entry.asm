extern kmain

global _start
_start:
	mov esp,[stack_end]

	push ebx ; multiboot information structure
	push eax ; multiboot magic number

	call kmain

	cli
	hlt

section .bss
stack:
	resb 0x4000 ; 16kB
stack_end:
