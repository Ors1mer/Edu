global flt2

;; Filters strings that contain exactly one "@"
;; and at least one "."
; flt2([ebp+8]: string address)
flt2:
		push	ebp
		mov		ebp, esp
		push	esi
		push	edi
		mov		edx, [ebp+8]	; save the address
		xor		eax, eax		; return boolean value
		xor		esi, esi		; "@" counter
		xor		edi, edi		; "." counter
.lp:	cmp		byte [edx], 0	; if end of string
		je		.rescheck		; check result and finish

		cmp		byte [edx], "@"
		je		.atinc
		cmp		byte [edx], "."
		je		.dotinc
		jmp		short .continue
.atinc:	inc		esi
		jmp		short .continue
.dotinc:
		inc		edi
.continue:
		inc		edx				; move to the next symbol
		jmp		.lp

.rescheck:
		xor		eax, eax
		cmp		esi, 1			; check "@" amount
		jne		.quit
		cmp		edi, 1			; "." amount
		jl		.quit
		inc		eax				; if ok, return true
.quit:	pop		edi
		pop		esi
		mov		esp, ebp
		pop		ebp
		ret
