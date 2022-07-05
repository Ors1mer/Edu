;; print_str.asm
%include "stud_io.inc"
global print_str

; print_str([ebp+8]: address of the string)
print_str:
		push	ebp
		mov		ebp, esp
		
		mov		eax, [ebp+8]	; store the address in eax, works faster
.lp:	cmp		[eax], byte 0	; if zero code,
		je		.quit			; string is printed, exit
		PUTCHAR byte [eax]
		inc		eax				; move to the next byte
		jmp		.lp
.quit:	mov		esp, ebp
		pop		ebp
		ret
