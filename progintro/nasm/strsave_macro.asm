%include "stud_io.inc"
global _start

%macro strsave 1		; arg: string literal
	%strlen l %1
	%assign n 1
	section .data
	string
	%rep l
		%substr sym %1 n	; get the last unsaved symbol
		%ifdef SIZE_TWO		; save the symbol to memory
			dw sym			; depending on the defined size
		%elifdef SIZE_FOUR
			dd sym
		%elifdef SIZE_EIGHT
			dq sym
		%else
			%error Please define SIZE_TWO, SIZE_FOUR, or SIZE_EIGHT
		%endif
		%assign n n+1		; move to the next
	%endrep
	section .text
%endmacro

section .text
_start:	strsave "It's so unreal"
		PUTCHAR [string]
