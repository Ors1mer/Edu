; The macros

%macro FINISH 1		; exitcode
	mov eax, 1
	mov	ebx, %1
	int	0x80
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

%macro PRINTINT 2	; dword int value & address of string
	push	esi		; stores the length of string

	push	%2		; string address
	push	%1		; integer
	call	int_to_str
	add		esp, 8

	push	%2
	call	strlen
	add		esp, 4
	mov		esi, eax
	PRINTSTR string, esi

	pop		esi
%endmacro

%macro PRINT 1
	push	eax
	push	ebx
	push	ecx
	push	edx
	jmp		%%syscall	; skip inits so CPU doesn't execute it
%%str		db %1		; save string to memory
%%len		equ $-%%str	; calculate length
%%syscall:
	mov		eax, 4
	mov		ebx, 1
	mov		ecx, %%str
	mov		edx, %%len
	int		0x80

	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
%endmacro
