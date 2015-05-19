global gdt_load
gdt_load:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]

	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:far_jump
far_jump:
	pop ebp
	ret
