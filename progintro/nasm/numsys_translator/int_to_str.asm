;; int_to_str.asm
global int_to_str

; Length of string should be at least 33
; int_to_str([ebp+8]: integer, [ebp+12]: string address, 
;								[ebp+16]: number system)
int_to_str:
		push	ebp
		mov		ebp, esp
		sub		esp, 4

		push	edi				; edi stores the address
		push	esi				; esi is the index
		mov		eax, [ebp+8]	; eax must store the number
		mov		edi, [ebp+12]	; write address to edi
		mov		[edi+33], byte 0	; indicates the end of the string
		mov		esi, 32			; esi must be the last index
		mov		ecx, [ebp+16]
		mov		[ebp-4], ecx	; save number system to local var
		cmp		dword [ebp-4], "A"	; if it's a letter
		jl		.sub_numsys
		sub		dword [ebp-4], 7	; remove gap between 9 and A
.sub_numsys:
		sub		dword [ebp-4], "0"	; get number from ASCII code

		test	eax, eax		; special case: eax == 0 since beginning
		jne		.lp
		mov		[edi], byte "0"	; write ASCII 0
		mov		[edi+1], byte 0	; indicate the end of string
		jmp		.quit

.lp:	test	eax, eax		; if eax is empty,
		je		.shift			; do shifting, then finish

		xor		edx, edx		; stores the remainder
		div		dword [ebp-4]	; divide eax by numsys base
		mov		byte [edi+esi], "0"
		add		[edi+esi], dl	; add the remainder to "0"

		cmp		dl, 9			; there's gap between 9 and A in ASCII
		jng		.finally
		add		byte [edi+esi], 7	; fill the gap
.finally:
		dec		esi
		jmp		.lp
.shift:	inc		esi				; esi is now index of the first digit
		mov		edx, 33
		sub		edx, esi		; edx is now the number of shifts
		cld						; shift to the right
.lp2:	test	edx, edx
		je		.quit
		mov		al, [edi+esi]	; store the digit in al
		stosb					; write digit to the left side
		dec		edx				; decrease counter
		jmp		.lp2
.quit:	pop		esi
		pop		edi
		mov		esp, ebp
		pop		ebp
		ret
