%include "stud_io.inc"
global _start

;; The program reads "num1 num2" from stdin
;; in decimal form, then writes their sum,
;; difference and product.

section .bss
num1		resd 1
num2		resd 1
num_str		resb 10

section .text
EOF		equ -1
newln	equ	10
_start:	xor eax, eax
		xor ecx, ecx
		mov ebp, 10
		xor esi, esi
		xor ebx, ebx		; bool: if num1 already entered
read_c:	GETCHAR
		cmp	eax, EOF
		je	quit_c
		cmp	eax, newln
		je	quit_c

		test ebx, ebx
		jne	num_check		; no need in space check if ebx > 0 already
		cmp eax, " "
		jne	num_check
		inc ebx				; if space, the rest of the chars are num2
		jmp read_c
num_check:
		cmp eax, "0"
		jl	err_exit
		cmp eax, "9"
		jg	err_exit

		mov	esi, eax		; save input character
		test ebx, ebx
		jne	num2_add
		mov eax, [num1]
		jmp continue
num2_add:
		mov eax, [num2]
continue:
		mul ebp				; mul 10
		sub esi, "0"
		add eax, esi

		test ebx, ebx
		jne	num2_save
		mov [num1], eax
		jmp finally
num2_save:
		mov [num2], eax
finally:
		xor eax, eax
		jmp read_c

quit_c:	xor ebx, ebx		; state variable
		mov esi, 9			; last index of num_str
		mov edi, esi		; current index of num_str
addn:	mov eax, [num1]
		add eax, [num2]
		jmp parse_c
subn:	mov eax, [num1]
		sub eax, [num2]
		jmp parse_c
muln:	mov eax, [num1]
		mul dword [num2]
		jmp parse_c

parse_c:
		test eax, eax
		je print_c
		xor edx, edx		; stores the remainder
		div ebp				; div 10
		add edx, "0"		; get ASCII code of the number
		mov [num_str + edi], dl
		dec edi
		jmp parse_c
print_c:
		cmp edi, esi
		jg next
		PUTCHAR [num_str + edi]
		inc edi
		jmp print_c
next:	inc ebx
		mov esi, 9
		mov edi, esi
		mov byte [num_str + esi], "0"
		PUTCHAR newln
		cmp ebx, 1			; addition was done
		je	subn
		cmp ebx, 2			; substitution
		je	muln
		jmp exit			; else finish the program

exit:	FINISH 0
err_exit:
		PRINT "Input error! Couldn't understand the character "
		PUTCHAR newln
		FINISH	1
