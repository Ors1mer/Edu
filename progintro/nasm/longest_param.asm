global	_start
extern	strlen

;; The program accepts any amount of arguments
;; and writes to stdout the biggest one

%macro FINISH 1
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

section .data
size	dd 0
newln	dw 10, 0
section .bss
indx	resd 1
addr	resd 1

section .text
_start:	mov		ecx, 2				; nth parameter

		cmp		dword [esp], 1		; if there are parameters,
		jne		lp					; continue
		FINISH	0					; else finish program
lp:		cmp		ecx, [esp]
		jg		lp_q
		mov		esi, [esp+4*ecx]	; parameter address

		push	esi
		call	strlen
		add		esp, 4

		cmp		eax, [size]
		jng		short finally
		mov		[size], eax
		mov		edi, [size]
		mov		[indx], ecx
		mov		[addr], esi
finally:
		inc		ecx
		jmp		lp
lp_q:	; Print the longest parameter
		mov		edi, [size]
		PRINTSTR [addr], [size]
		; Print new line
		PRINTSTR newln, 1
		FINISH	0
