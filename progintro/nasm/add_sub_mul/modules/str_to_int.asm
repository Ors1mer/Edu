;; str_to_int.asm
global str_to_int

; str_to_int([ebp+8]: address of a string, [ebp+12]: length)
str_to_int:
		push	ebp
		mov		ebp, esp
		sub		esp, 4			; local variable ten32
		push	edi				; counter for iterations
		push	esi				; string address
		push	ebx				; character from the string
		xor		eax, eax		; return value
		xor		ebx, ebx
		xor		edi, edi
		mov		[ebp-4], dword 10
		mov		esi, [ebp+8]	; write str address to esi
.lp:	cmp		edi, [ebp+12]	; compare edi and length of the str
		je		.quit			; quit if equal
		mov		bl, [esi+edi]

		cmp		ebx, "0"		; check if the character is a number,
		jl		.err			; in case it's not rise error
		cmp		ebx, "9"		; and quit
		jg		.err

		sub		ebx, "0"		; get the number from ASCII code
		mul		dword [ebp-4]	; multiply eax by 10
		add		eax, ebx		; add the number to the result
		inc		edi				; increase counter
		jmp		.lp

.err:	mov		ecx, -1			; if error occured, make ecx = -1
.quit:	pop		ebx				; restore initial ebx
		pop		esi				; ...esi
		pop		edi				; ...edi
		mov		esp, ebp
		pop		ebp
		ret
