%include "stud_io.inc"
global _start

;; The program reads text from stdin until EOF,
;; then prints amount of symbols entered in
;; decimal form.

section .bss
num_str	resb 10

section .text
EOF		equ	-1
_start:	xor	eax, eax	; character from stdin, later nominator
		xor ecx, ecx	; symbol count
		xor edx, edx	; remainder of division
		mov ebx, 10		; the divisioner
		mov esi, 9		; the last index of num_str
		mov edi, esi	; the current index of num_str
read_c:	GETCHAR
		cmp	eax, EOF
		je	quit_c

		inc ecx
		jmp read_c
quit_c:	PUTCHAR 10
		mov	eax, ecx
parse_c:
		test eax, eax
		je	print_c

		xor edx, edx
		div ebx
		add edx, "0"	; get ASCII code of the number
		mov [num_str + edi], dl

		dec edi
		jmp parse_c
print_c:
		cmp	edi, esi
		jg	exit
		PUTCHAR [num_str + edi]
		inc	edi
		jmp print_c
exit:	PUTCHAR 10
		FINISH	0
