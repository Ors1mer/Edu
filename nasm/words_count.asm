%include "stud_io.inc"
global _start

;; The program reads lines from stdin
;; until EOF, and prints '*' amount_of_words
;; times for each line just after it was entered.
;; Word is simply an array of chars that is
;; separated by spaces

section .text
newln	equ 10
space	equ 32
EOF		equ -1

_start:	xor eax, eax	; character from stdin
		xor ecx, ecx	; words count in the line
		xor ebx, ebx	; length of the current word
read_c:	GETCHAR
		cmp	eax, EOF	; if EOF,
		je	add_w		; add word, print amount, then exit

		cmp eax, newln	; if newline,
		je	add_w		; add word, print amount
						; then empty ecx & ebx and continue

		cmp eax, space	; if space,
		je	add_w		; ecx++, empty ebx

		inc ebx			; else ebx++
		jmp read_c

add_w:	cmp	ebx, 0
		je	after
		inc ecx
after:	cmp	eax, space
		je	clear_word
		jmp	print_w		; else EOF or newline
clear_word:
		xor ebx, ebx
		jmp read_c
print_w:
		cmp	ecx, 0
		je	continue
		PUTCHAR "*"
		dec	ecx
		jmp	print_w
continue:
		PUTCHAR newln
		cmp eax, newln
		je	_start
exit:	FINISH 0
