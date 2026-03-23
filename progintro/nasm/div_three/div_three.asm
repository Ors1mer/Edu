%include "kernel.inc"
global _start

;; The program requires one parameter,
;; which should be a decimal number of
;; any length. The program writes "OK"
;; to stdin if the number is a multiple
;; of 3.

; Works faster then kernel
%macro FINISH 1		; exitcode
	mov eax, 1
	mov	ebx, %1
	int	0x80
%endmacro

section .data
msg		db "OK", 10
lenmsg	equ $-msg
three32	dd 3

section .text
newln	equ 10
stdin	equ 1
write	equ 4

_start:	xor		eax, eax		; the sum of digits
		xor		ebx, ebx		; temp variable
		cmp		dword [esp], 2
		jl		.err_arg

		mov		esi, [esp+8]	; number's address
.lp:	cmp		byte [esi], 0
		je		.lp_q
		
		cmp		byte [esi], "0"
		jl		.err_num
		cmp		byte [esi], "9"
		jg		.err_num

		sub		byte [esi], "0"
		mov		bl, [esi]
		add		eax, ebx

		inc		esi
		jmp		.lp
.lp_q:	div		dword [three32]
		test	edx, edx
		jne		.fail
		kernel	write, stdin, msg, lenmsg
.fail:	FINISH	0
.err_arg:
		FINISH	1
.err_num:
		FINISH	2
