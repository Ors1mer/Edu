;; str_to_int.asm
global str_to_int

; str_to_int([ebp+8]: address of a string, [ebp+12]: length, 
;									[ebp+16]: number system)
str_to_int:
		push	ebp
		mov		ebp, esp
		sub		esp, 4			; memory for local var
		push	edi				; counter for iterations
		push	esi				; string address
		push	ebx				; character from the string

		xor		eax, eax		; return value
		xor		edi, edi
		mov		esi, [ebp+8]	; write str address to esi
		mov		ebx, [ebp+16]
		mov		[ebp-4], ebx
		xor		ebx, ebx
		cmp		dword [ebp-4], "A"	; if it's a letter
		jl		.sub_numsys
		sub		dword [ebp-4], 7	; remove gap between 9 and A
.sub_numsys:
		sub		dword [ebp-4], "0"	; get number from ASCII code
.lp:	cmp		edi, [ebp+12]	; compare edi and length of the str
		je		.quit			; quit if equal
		mov		bl, [esi+edi]

		cmp		ebx, "0"		; check if the character is a digit,
		jl		.err			; in case it's not rise error
		cmp		ebx, [ebp+16]	; and quit
		jge		.err

		cmp		ebx, "A"		; there's gap between A and 9
		jl		.next
		sub		ebx, 7			; remove the gap
.next:	sub		ebx, "0"		; get the number from ASCII code
		mul		dword [ebp-4]	; multiply eax by the numsys base
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
