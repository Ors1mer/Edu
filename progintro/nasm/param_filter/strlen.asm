global strlen

; strlen([ebp+8]: string address)
strlen:
		push	ebp
		mov		ebp, esp
		mov		edx, [ebp+8]	; save address
		xor		eax, eax		; length of the string
.lp:	cmp		byte [edx+eax], 0
		je		.quit
		inc		eax
		jmp		short .lp
.quit:	mov		esp, ebp
		pop		ebp
		ret
