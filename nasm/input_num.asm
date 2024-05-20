%include "stud_io.inc"
global _start

;; The program prints '*' n times depending on the input
;; If not a number given, it prints nothing

section	.text
_start: xor		al, al
		GETCHAR
		cmp		al, 47	; numbers in ASCII start from 48
		jg		less
		FINISH	1
less:	cmp		al, 58	; and end at 57
		jl		write
		FINISH	1
write:	cmp		al, 48	; write '*' while number > '0'
		jna		end		; quit cycle if equal to '0'
		PRINT	"*"
		dec		al
		jmp		short write
end:	PUTCHAR	10
		FINISH	0
