%include "stud_io.inc"
global _start

;; The program behaves like cat when no parameters given
;; Reads input and prints it, until EOF

section .bss
string resb 1024

section	.text
_start:	xor eax, eax
		xor ecx, ecx
		xor ebx, ebx
read_c:	GETCHAR
		cmp eax, -1		; EOF check
		je	quit		; end the program
		cmp eax, 10		; Newline check
		je	input_done	; end the cycle
		mov	[string+ecx], al
		inc	ecx
		jmp	read_c
input_done:
		cmp	ecx, 0		; if no input
		je	startover
		mov ebx, ecx	; store the string size
		xor ecx, ecx
write_c:
		cmp	ebx, ecx	; check if string printed
		jl	startover
		PUTCHAR	[string+ecx]
		inc	ecx
		jmp	write_c
startover:
		PUTCHAR 10
		jmp _start
quit:	FINISH	0
