%include "stud_io.inc"
global _start

;; The program reads "num1[+,-,*,/]num2" from stdin
;; in decimal form, then does specified action and
;; writes result also in decimal form.
;; Only unsigned numbers are supported.
;; Division by zero writes error.
;; The program ends when EOF.

section .data
ten32	dd	10

section .bss
act		resb 1				; the action sign: +, -, *, /
num1	resd 1
num2	resd 1
num_str	resb 10				; the answer in decimal form

section .text
EOF		equ -1
newln	equ 10
_start:	xor		eax, eax
		xor		edx, edx
		xor		ebx, ebx	; bool: if num2 is being read
		xor		ecx, ecx
		mov		esi, 9		; last index of num_str
		xor		edi, edi
lp:		cmp		edi, esi
		jg		lp_q
		mov		byte [num_str + edi], 0
		inc		edi
		jmp		lp
lp_q:	mov		dword [num1], 0
		mov		dword [num2], 0
read_c:	GETCHAR
		cmp		eax, EOF
		je		exit
		cmp		eax, newln
		je		read_q

		test	ebx, ebx	; if num2 being read,
		jne		digit_save	; don't look for action sign
		cmp		eax, "+"
		je		sign_save
		cmp		eax, "-"
		je		sign_save
		cmp		eax, "*"
		je		sign_save
		cmp		eax, "/"
		jne		digit_save
sign_save:
		mov		[act], al	; save action in the variable
		inc		ebx			; read num2 in further iterations
		jmp		read_c		; continue reading
digit_save:
		cmp		eax, "0"
		jl		err_continue
		cmp		eax, "9"
		jg		err_continue
		; --- Saving digit ---
		sub		eax, "0"
		mov		esi, eax
		test	ebx, ebx	; decides which number to increase
		jne		num2_a
num1_a:	mov		eax, [num1]
		jmp		if1_q
num2_a:	mov		eax, [num2]
if1_q:	mul		dword [ten32]	; multiply num in eax by 10
		add		eax, esi
		; Save eax to num1/num2
		test	ebx, ebx
		jne		num2_s
num1_s:	mov		[num1], eax
		jmp		read_c
num2_s:	mov		[num2], eax
		jmp		read_c

read_q:	;mov		esi, 9			; last index of num_str
		mov		edi, esi		; current index of num_str
		xor		eax, eax
		mov		eax, [num1]		; nums must be stored
		mov		ecx, [num2]		; in eax & ecx
		cmp		byte [act], "+"
		je		pls
		cmp		byte [act], "-"
		je		min
		cmp		byte [act], "*"
		je		prd
		cmp		byte [act], "/"
		je		dvn
pls:	add		eax, ecx
		jmp		parse_c
min:	sub		eax, ecx
		jmp		parse_c
prd:	mul		ecx
		jmp		parse_c
dvn:	test	ecx, ecx		; if division by zero,
		je		err_zerodiv		; write error & start reading over
		div		ecx

parse_c:
		test	eax, eax
		je		print_c
		xor		edx, edx		; stores the remainder
		div		dword [ten32]	; div 10
		add		edx, "0"		; get ASCII code of the number
		mov		[num_str + edi], dl
		dec		edi
		jmp		parse_c
print_c:
		cmp		edi, esi
		jg		print_q
		PUTCHAR	[num_str + edi]
		inc		edi
		jmp		print_c
print_q:
		PUTCHAR	newln
		jmp		_start

err_continue:
		PRINT	"Error"
		jmp		print_q
err_zerodiv:
		PRINT	"Error: division by zero is not allowed!"
		jmp		print_q
exit:	PUTCHAR	newln
		FINISH	0
