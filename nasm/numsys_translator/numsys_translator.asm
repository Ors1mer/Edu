%include "stdio.inc"
global _start
extern str_to_int
extern int_to_str
extern strlen

;; The program reads three parameters:
;; the first two are bases of number systems,
;; the program should translate the third parameter
;; from the first numsys to the second.
;; (All input letters should be uppercase)
;; In case of wrong parameters write nothing and
;; return non-zero exitcode.

section .bss
num		resd 1
string	resb 33

section .text
jmp		_start
newln	db 10, 0

_start:	cmp		dword [esp], 4	; check amount of command line args
		jne		err_args
		mov		esi, [esp+8]
		mov		ecx, 12
		; Number systems check
		mov		edi, [esp+16]	; address of the 3rd argument
again:	cmp		byte [esi+1], 0
		jne		err_sys
		mov		eax, [esi]		; DEBUG
		cmp		byte [esi], "2"
		jl		err_sys
		cmp		byte [esi], "9"
		jg		short .letter
		jmp		short .fin
.letter:
		cmp		byte [esi], "A"
		jl		err_sys
		cmp		byte [esi], "Z"
		jg		err_sys
.fin:	mov		esi, [esp+ecx]
		add		ecx, 4
		cmp		esi, edi
		jne		short again
		; Convert the number into binary
		mov		ebp, esp		; save stack pointer
		mov		esi, [ebp+8]	; store the address of numsys
		xor		ebx, ebx
		mov		bl, [esi]		; store the numsys in ebx

		push	ebx				; push number system

		push	dword [ebp+16]	; push given number addr for strlen
		call	strlen			; calculate length
		add		esp, 4

		push	eax				; push the length
		push	dword [ebp+16]	; push given number addr for str_to_int
		mov		esi, [ebp+16]
		mov		bl, [esi]
		call	str_to_int		; calculate the number
		add		esp, 12
		cmp		ecx, -1			; check if error was returned
		je		err_num
		; Convert the number into the second number system
		mov		esi, [ebp+12]
		xor		ebx, ebx
		mov		bl, [esi]
		push	ebx				; push number system
		push	string			; push the string address to save result
		push	eax				; push the obtained number
		call	int_to_str
		add		esp, 12

		push	string
		call	strlen
		add		esp, 4
		mov		edi, eax

		PRINTSTR string, edi
		PRINTSTR newln, 1

		FINISH	0
err_args:	; argc != 3
		FINISH	1
err_sys:	; bad number system
		FINISH	2
err_num:	; bad number
		FINISH	3
