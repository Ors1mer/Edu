global _start
extern strlen
extern cmp_ends

;; The program accepts command line parameters
;; and finishes successfully if two params given
;; and: (params have the same length) or
;; (params end with the same symbol)

%macro FINISH 1	; FINISH exitcode
	mov eax, 1	; code for _exit
	mov ebx, %1	; write exitcode
	int 0x80	; do syscall
%endmacro

section .bss
len1	resd 1
len2	resd 1

section .text
_start:	cmp		dword [esp], 3	; check amount of params
		je		cmp_len			; if ok, go on
		FINISH	1				; else finish with errcode 1
cmp_len:
		; Calculate lengths for each param
		mov		ebx, [esp]		; arg count
		dec		ebx				; exclude program name
		mov		esi, esp
		add		esi, 8			; args
again:	push	dword [esi]		; push args[i]
		call	strlen
		add		esp, 4
		add		esi, 4
		cmp		ebx, 2
		jne		short else
		mov		[len1], eax
		jmp		short next
else:	mov		[len2], eax
next:	dec		ebx
		jnz		again

		mov		ebx, [len1]
		cmp		ebx, [len2]
		jne		cmp_ending
		FINISH	0
cmp_ending:
		push	dword [len2]
		push	dword [len1]
		push	dword [esi-4]
		push	dword [esi-8]
		call	cmp_ends
		add		esp, 16

		test	eax, eax
		je		err_exit
		FINISH	0
err_exit:
		FINISH	1
