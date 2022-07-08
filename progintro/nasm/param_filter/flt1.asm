global flt1

;; Filters string with at least one uppercase letter
; flt1([ebp+8]: string address)
flt1:
		push	ebp
		mov		ebp, esp
		mov		edx, [ebp+8]	; save the address
		xor		eax, eax		; return boolean value

.lp:	cmp		byte [edx], 0	; if end of string
		je		.quit			; finish

		cmp		byte [edx], "A"
		jl		.continue
		cmp		byte [edx], "Z"
		jg		.continue
		inc		eax
		jmp		.quit
.continue:
		inc		edx				; move to the next symbol
		jmp		.lp
.quit:	mov		esp, ebp
		pop		ebp
		ret
