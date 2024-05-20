%include "stdio.inc"
global _start
extern str_to_int
extern int_to_str
extern strlen

;; The program accepts 2 command line parameters,
;; which are numbers in octal form, then writes
; their sum and product also in octal form.

section .data
newln	db 10, 0

section .bss
num1	resd 1
num2	resd 1
string	resb 11

section .text
_start:	cmp	dword [esp], 3	; check amount of command line args
		jne	err_args

		xor		ebx, ebx
		mov		esi, esp
		add		esi, 8
again:	push	dword [esi]
		call	strlen
		add		esp, 4

		push	eax
		push	dword [esi]
		call	str_to_int
		add		esp, 8

		test	ebx, ebx
		jne		num2save
		mov		[num1], eax
		jmp		short finally
num2save:
		mov		[num2], eax
finally:
		add		esi, 4
		inc		ebx
		cmp		ebx, 1
		je		again

addn:	mov		eax, [num1]
		add		eax, [num2]

		PRINTINT eax, string
		PRINTSTR newln, 1
clearb:	cmp		ecx, 11			; clear the string from previous value
		je		muln
		mov		byte [string+ecx], 0
		inc		ecx
		jmp		clearb

muln:	mov		eax, [num1]
		mul		dword [num2]
		PRINTINT eax, string
		PRINTSTR newln, 1
		FINISH	0
err_args:
		cmp		dword [esp], 3
		jg		.toomany
		PRINT	"Not enough arguments!"
		PRINTSTR newln, 1
		jmp		short err_exit
.toomany:
		PRINT	"Too many arguments!"
		PRINTSTR newln, 1
err_exit:
		FINISH	1
