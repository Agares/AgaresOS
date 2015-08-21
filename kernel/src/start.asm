section .text
extern kmain
global _start

_start:
	mov rsp, stack_end
	call kmain

	cli
	.loop:
		hlt
		jmp .loop

section .bss
stack:
	resb 16384 ; 16kB
stack_end:
