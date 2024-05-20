%include "stud_io.inc"
global _start

;; The program reads one line from stdin,
;; then writes the same line in reverse order.

section .text
EOF		equ -1
newln	equ 10
_start:	xor		eax, eax
		xor		ecx, ecx
read_c:	GETCHAR
		cmp		eax, EOF
		je		read_q
		cmp		eax, newln
		je		read_q

		push	eax			; push eax to the stack
		inc		ecx			; count symbols
		jmp		read_c
read_q:	cmp		eax, EOF
		jne		write_c
		PUTCHAR	newln
write_c:
		test	ecx, ecx
		je		exit
		pop		eax			; get eax from the stack
		PUTCHAR	al			; write the first byte from eax
		dec		ecx
		jmp		write_c
exit:	PUTCHAR	newln
		FINISH	0
