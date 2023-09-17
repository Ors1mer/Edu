global strlen

; strlen([ebp+8]: string address)
strlen:
		push	ebp
		mov		ebp, esp
		mov		edx, [ebp+8]		; save address
		xor		eax, eax			; length of the string
.lp:	cmp		byte [edx+eax], 0	; if the char == 0,
		je		.quit				; finish
		inc		eax					; else length++
		jmp		short .lp			; start over
.quit:	mov		esp, ebp
		pop		ebp
		ret
