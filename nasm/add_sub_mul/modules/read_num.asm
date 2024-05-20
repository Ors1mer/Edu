;; read_num.asm
%include "stud_io.inc"
global read_num

; read_num([ebp+8]: address where to save number, [ebp+12]: size)
read_num:
		push	ebp
		mov		ebp, esp
		xor		ecx, ecx
		mov		edx, [ebp+8]	; save address to edx
.lp:	GETCHAR
		cmp		eax, -1			; EOF check
		je		.quit
		cmp		eax, "0"
		jl		.quit
		cmp		eax, "9"
		jg		.quit

		cmp		ecx, [ebp+12]	; check if max number already entered
		jge		.err_size

		mov		[edx+ecx], al
		inc		ecx
		jmp		.lp
.err_size:
		mov		eax, -2			; means that number was too big
.quit:	mov		esp, ebp
		pop		ebp
		ret
