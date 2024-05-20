%include "stud_io.inc"
global _start

;; The program reads lines from stdin,
;; then writes the same lines, but each
;; in reverse order.

section .text
EOF		equ -1
newln	equ 10
_start:	xor		eax, eax
		xor		ebx, ebx
		xor		ecx, ecx
		xor		esi, esi	; the index of next newline in the stack
		xor		edi, edi	; current index in the stack
read_c:	GETCHAR				; save all symbols in the stack
		cmp		eax, EOF
		je		read_q

		push	eax			; push 4-byte value to the stack
		inc		ecx			; count symbols
		jmp		read_c
read_q:	PUTCHAR	newln
write_c:
		test	ecx, ecx	; if ecx == 0
		jle		exit		; end the cycle
		mov		esi, ecx
		; Find the next newline in the stack
lp:		test	esi, esi	; if hit bottom,
		jl		lp_q		; quit
		cmp		[esp + 4*esi], dword newln
		je		lp_q

		dec		esi
		jmp		lp
lp_q:	mov		edi, esi
		inc		edi			; edi now points at symbol before newline
		; Print the line in reverse order
lp2:	cmp		edi, ecx
		jg		lp2_q
		mov		ebx, [esp + 4*edi]
		PUTCHAR	bl
		inc		edi
		jmp		lp2
lp2_q:	PUTCHAR	newln
		dec		esi
		mov		ecx, esi
		jmp		write_c
exit:	FINISH	0
