global cmp_ends

; cmp_ends([ebp+8]: str1 address, [ebp+12]: str2 address
;			[ebp+16]: strlen1, [ebp+20]: strlen2)
cmp_ends:
		push	ebp
		mov		ebp, esp
		push	ebx
		push	edi

		xor		eax, eax		; return bool value
		mov		edx, [ebp+8]	; first address
		add		edx, [ebp+16]
		dec		edx
		mov		ecx, [ebp+12]	; second address
		add		ecx, [ebp+20]
		dec		ecx

		mov		bl, [edx]
		cmp		bl, [ecx]
		jne		.quit
		inc		eax
.quit:	pop		ebx
		mov		esp, ebp
		pop		ebp
		ret
