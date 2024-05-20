%include "stud_io.inc"
global _start

;; The program reads a number from stdin,
;; then prints "*" number times.

section .text
_start:	xor		eax, eax	; character from stdin
		mov		ebx, 10		; the multiplier
		xor		ecx, ecx	; the binary number
read_c:	GETCHAR
		cmp		eax, "0"	; if not a number given,
		jl		print_c		; end the cycle
		cmp		eax, "9"	; and start printing "*"
		jg		print_c
							; else change the number ecx
		mov		esi, eax	; save input character
		mov		eax, ecx	; since eax is used in multiplication

		mul		ebx			; eax *= 10
		sub		esi, "0"
		add		eax, esi
		mov		ecx, eax
		xor		eax, eax	; erase eax for further reading
		jmp		read_c
print_c:
		test	ecx, ecx
		jng		exit
		PUTCHAR	"*"
		dec		ecx
		jmp		print_c
exit:	PUTCHAR 10
		FINISH	0
