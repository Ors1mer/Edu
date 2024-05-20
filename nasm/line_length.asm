%include "stud_io.inc"
global _start

;; The program reads lines and writes
;; '*' length_of_line times after EOF given

section .bss
llens	resw 256		; lines lengths

section .text
newln	equ 10
EOF		equ -1

_start:	xor eax, eax	; stores char value from stdin
		xor cx,	cx		; stores the length of line (2 bytes)
		xor ebx, ebx	; stores the length of llens
		xor edx, edx	; counter for print_lens
read_c:	GETCHAR
		cmp	eax, EOF	; if EOF,
		je	save_len	; save length & start printing

		cmp eax, newln	; if newline,
		je	save_len	; save the length of the line

		inc cx			; else cx++
		jmp read_c
save_len:
		inc bx
		mov [llens + 2*ebx], cx
		xor cx, cx
		cmp	eax, EOF	; if EOF,
		je	print_lens	; stop reading & start printing

		jmp read_c		; else continue reading
print_lens:
		cmp	dx, bx		; if at the end of the list,
		jnle exit		; finish the program

		mov cx, [llens + 2*edx]
		inc dx
		PUTCHAR newln

print_len:
		cmp cx, 0
		je	print_lens

		PUTCHAR "*"
		dec cx
		jmp print_len
exit:	PUTCHAR	newln
		FINISH	0
