%include "stud_io.inc"
global _start

;; The program reads lines (256 max),
;; then writes '*' longest_word times,
;; then ' ' and '*' last_word times
;; for each entered line respectively

section .bss
maxw	resw 256		; the longest words
lastw	resw 256		; the last words

section .text
newln	equ 10
space	equ	32
EOF		equ -1

_start:	xor eax, eax	; stores char value from stdin
		xor cx, cx		; stores the length of a word (2 bytes)
		xor ebx, ebx	; stores the amount of entered lines
		xor edx, edx	; used as a counter
read_c:	GETCHAR
		cmp eax, EOF	; if EOF,
		je	print		; save line's words & start printing

		cmp eax, newln	; if newline,
		je	save_words	; save line's words & ebx++

		cmp eax, space	; if space,
		je	compare		; compare max word vs entered word,
						; then empty cx

		inc cx			; else cx++
		jmp	read_c
;; Case of space
compare:
		cmp	cx, [maxw + 2*ebx]
		jg	change_max
		jmp empty
change_max:
		mov [maxw + 2*ebx], cx
empty:	xor cx, cx
		cmp eax, space	; if space,
		je	read_c		; continue reading
		jmp inc_ln		; else do ebx++
;; Case of newline
save_words:
		mov [lastw + 2*ebx], cx
		jmp compare		; check if the last word also is
						; the biggest one
inc_ln: cmp	eax, EOF	; if EOF,
		je	print_lns	; start printing
		inc ebx			; else ebx++
		jmp read_c		; and continue reading
;; Case of EOF
print:	PUTCHAR newln
		jmp save_words
print_lns:
		cmp edx, ebx	; if all printed already,
		jnle exit		; end the program

		mov cx, [maxw + 2*edx]
pr_max:	cmp cx, 0		; print length of the longest word
		jng	exit_max_lp
		PUTCHAR "*"
		dec cx
		jmp pr_max
exit_max_lp:
		PUTCHAR space

		mov cx, [lastw + 2*edx]
pr_lst:	cmp	cx, 0		; print length of the last word
		jng exit_lst_lp
		PUTCHAR "*"
		dec cx
		jmp pr_lst
exit_lst_lp:
		PUTCHAR newln
		inc edx
		jmp print_lns

exit:	FINISH 0
