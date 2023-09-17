; The system calls macros

%macro FINISH 1		; exitcode
					; no point in pushing as the program ends
	mov eax, 1		; syscall code for _exit
	mov	ebx, %1		; write exitcode
	int	0x80		; do the system call
%endmacro

%macro PUTCHAR 1	; character to print
	push	eax
	push	ebx
	push	ecx
	push	edx

	sub		esp, 4
	xor		edx, edx
	mov		dl, %1			; save the argument in dl
	mov		[esp], edx		; put the argument on top of the stack

	mov		ecx, esp		; address of the character

	mov		eax, 4			; write syscall
	mov		ebx, 1			; stdout
	mov		edx, 1			; length
	int		0x80
	add		esp, 4

	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
%endmacro


%macro PRINTSTR 2	; address and length
	push	eax
	push	ebx
	push	ecx
	push	edx

	mov		eax, 4	; write syscall
	mov		ebx, 1	; stdout
	mov		ecx, %1	; address
	mov		edx, %2	; length
	int		0x80

	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
%endmacro

