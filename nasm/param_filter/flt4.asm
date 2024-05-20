global flt4

;; Filters strings that consist of
;; only the same symbol
; flt4([ebp+8]: string address)
flt4:
		push	ebp
		mov		ebp, esp
		mov		edx, [ebp+8]	; save the address
		mov		eax, 1			; return bool, true at the beginning
		mov		cl, [edx]		; the symbol for comparisons
.lp:	cmp		byte [edx], 0	; if end of string
		je		.quit			; finish with true

		cmp		cl, [edx]
		je		.continue
		xor		eax, eax		; make eax false
		jmp		.quit			; and finish function
.continue:
		inc		edx				; move to the next symbol
		jmp		.lp
.quit:	mov		esp, ebp
		pop		ebp
		ret
