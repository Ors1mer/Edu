%include "stud_io.inc"
global _start

;; The program reads a number from stdin,
;; then prints "*" number times.

section .data
num_int	dd 0
deg		dw -1
ten		dd 10

section .bss
num_str	resb 10
digit	resd 1
pow10	resd 1

section .text
_start:	xor eax, eax	; character from stdin
		mov	ebx, -1		; length of num_str (including 0)
read_c:	GETCHAR
		cmp eax, "0"	; if not a number given,
		jl	quit_c		; end the cycle
		cmp eax, "9"
		jg	quit_c

		inc ebx
		mov [num_str + ebx], al
		jmp read_c

quit_c:	mov ecx, ebx	; loop goes from last to first el
		xor eax, eax	; eax is now used in mul
parse_c:
		test ecx, ecx	; cmp ecx, 0
		jnge quit_parse_c
		; Get needed degree & 10^degree
		inc	word [deg]
		mov eax, 1
		push ecx
		xor cx, cx
pow_c:	cmp	cx, [deg]
		jnl	quit_pow_c
		mul	dword [ten]
		inc	cx
		jmp	pow_c
quit_pow_c:
		pop ecx
		; Get the digit from num_str
		sub	byte [num_str + ecx], "0"
		mov	dl, [num_str + ecx]
		mov	[digit], edx
		; Multiply 10^deg by digit
		mul	dword [digit]

		add	[num_int], eax
		dec ecx
		jmp parse_c

quit_parse_c:
		mov ecx, [num_int]
print_c:
		test	ecx, ecx
		jng		exit
		PUTCHAR	"*"
		dec		ecx
		jmp		print_c

exit:	PUTCHAR 10
		FINISH 0
