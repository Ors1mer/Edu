;; int_to_str.asm
global int_to_str

; Uses octal number system
; int_to_str([ebp+8]: integer, [ebp+12]: string address)
int_to_str:
		push	ebp
		mov		ebp, esp
		sub		esp, 4

		push	edi				; edi stores the address
		push	esi				; esi is the index
		mov		eax, [ebp+8]	; eax must store the number
		mov		edi, [ebp+12]	; write address to edi
		mov		[edi+10], byte 0	; indicates the end of the string
		mov		esi, 9			; esi must be the last index
		mov		[ebp-4], dword 8	; write 8 to local variable

		test	eax, eax		; special case: eax == 0 since beginning
		jne		.lp
		mov		[edi], byte "0"	; write the number 0
		mov		[edi+1], byte 0	; indicate the end of string
		jmp		.quit

.lp:	test	eax, eax		; if eax is empty,
		je		.shift			; do shifting, then finish

		xor		edx, edx		; stores the remainder
		div		dword [ebp-4]	; divide eax by 8
		mov		[edi+esi], byte "0"
		add		[edi+esi], dl

		dec		esi
		jmp		.lp
.shift:	inc		esi				; esi is now index of the first digit
		mov		edx, 11
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
