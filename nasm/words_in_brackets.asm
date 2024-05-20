%include "stud_io.inc"
global _start

;; The program reads text from stdin
;; until EOF, and prints the same text,
;; but each word in brackets "()".
;; maximum size of text is 2048 symbols.

section .bss
text	resb 2048

section .text
newln	equ 10
space	equ 32
EOF		equ -1
open_b	equ	40
close_b	equ	41

_start:	xor eax, eax	; character from stdin
		xor ebx, ebx	; length of the text
		xor ecx, ecx	; used as a counter
read_c:	GETCHAR
		cmp	eax, EOF	; if EOF,
		je	quit_c		; stop reading & start printing

		mov [text + ebx], al ; else save character to array
		inc ebx
		jmp read_c

quit_c:	PUTCHAR newln
		dec ebx
print:	cmp [text + ecx], byte space
		je	space_check
		cmp [text + ecx], byte newln
		je	space_check
		jmp char_check

char_check:
		cmp ecx, 0
		je	pr_open
		cmp ecx, ebx
		jg	exit

		dec ecx
		cmp	[text + ecx], byte space
		je pr_open
		cmp [text + ecx], byte newln
		je pr_open
		jmp recover
pr_open:
		PUTCHAR open_b
		jmp recover
space_check:
		cmp ecx, 0
		je	print_char

		dec ecx			; look at the previous char
		cmp [text + ecx], byte space
		je	recover
		cmp [text + ecx], byte newln
		je	recover
pr_close:
		PUTCHAR close_b
recover:
		cmp ecx, 0
		jne	incr
		PUTCHAR [text]
incr:	inc ecx
print_char:
		PUTCHAR [text + ecx]
		inc ecx
		cmp ecx, ebx
		jnle exit
		jmp print

exit:	cmp	[text + ebx], byte space
		je	end
		cmp [text + ebx], byte newln
		je	end
		PUTCHAR close_b
end:	PUTCHAR newln
		FINISH 0
