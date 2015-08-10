global gdt_load
global gdt_load_64

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

	jmp 0x08:.far_jump
.far_jump:
	pop ebp
	ret

gdt_load_64:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov edi, [ebp+20]

	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:.far_jump
.far_jump:
	db 0x48 ; mov rax, [esp+12]
	db 0x8b
	db 0x45
	db 0x0c
	db 0xff ; jmp rax
	db 0xe0
