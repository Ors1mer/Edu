%include "stud_io.inc"
global _start

;; The program reads lines from stdin and
;; calculates the sum of digits in the string
;; and prints '*' sum_of_digits times

section .text
EOF		equ -1
newln	equ 10

_start:	xor eax, eax	; stores char value from stdin
		xor ebx, ebx	; stores the sum
read_c:	GETCHAR
		cmp	eax, `0`	; if greater than '0'
		jg	greater_0	; do further check

		cmp eax, newln	; if newline given,
		je	print_sum	; print obtained sum & clear ebx

		cmp eax, EOF	; if EOF given,
		je	exit		; end the program

		jmp read_c		; else continue reading stdin
greater_0:
		cmp eax, `9`	; ... and also less-equal than '9',
		jna	number_add	; then char is a number,
		jmp read_c		; else return to reading stdin
number_add:
		sub eax, `0`	; get actual number from ASCII code,
		add ebx, eax	; then add to the sum
		jmp read_c
print_sum:
		cmp	ebx, 0
		je	start_over	; end cycle
		PUTCHAR `*`
		dec ebx
		jmp print_sum	; continue cycle
start_over:
		PUTCHAR newln
		jmp	read_c
exit:	FINISH 0
