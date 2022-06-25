%include "stud_io.inc"
global _start

;; The program counts pluses & minuses from stdin,
;; then writes to stdout '*' pluses*minuses times

section .text
EOF		equ	-1
newl	equ	10
_start:	xor eax, eax
		xor ebx, ebx	; '+' counter
		xor edx, edx	; '-' counter
read:	GETCHAR
		cmp	eax, "+"
		je	inc_p
		cmp eax, "-"
		je	inc_m
		cmp	eax, newl
		je	multiply
		cmp eax, EOF
		je multiply
		jmp read
inc_p:
		inc ebx
		jmp read
inc_m:
		inc edx
		jmp read
multiply:
		mov	eax, ebx
		mul	edx
print_c:
		cmp eax, 0
		jng exit		; exit if eax == 0
		PRINT "*"
		dec eax
		jmp print_c
exit:	PUTCHAR 10
		FINISH 0
