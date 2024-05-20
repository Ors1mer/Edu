global flt3
extern strlen

;; Filters strings that start with uppercase
;; and end with lowercase letter.
; flt3([ebp+8]: string address)
flt3:
		push	ebp
		mov		ebp, esp
		mov		edx, [ebp+8]	; save the address
		xor		eax, eax		; return boolean value
		; Check the first symbol
		cmp		byte [edx], "A"
		jl		.quit
		cmp		byte [edx], "Z"
		jg		.quit
		; Check the last symbol
		push	edx
		call	strlen
		add		esp, 4
		mov		ecx, eax		; store the length in ecx
		xor		eax, eax		; clear return value
		cmp		byte [edx+ecx-1], "a"
		jl		.quit
		cmp		byte [edx+ecx-1], "z"
		jg		.quit
		inc		eax
.quit:	mov		esp, ebp
		pop		ebp
		ret
