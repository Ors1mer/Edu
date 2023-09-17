;; main.asm
;; NASM 2.16.01

;; The program requires one command line argument that will be the pyramid's
;; base. The pyramid shrinks in width by two characters per line towards the
;; top. There's always only one symbol at the top.

%include "stdio.inc"
global _start
extern strlen

section	.bss
straddr resd 1	; address of the initial string
length	resd 1	; the length of the given string
range	resd 2	; the beginning and the end of the line to print

section	.text
jmp		_start	; don't execute the next line
newln	equ 10	; newline character alias

_start:	cmp		dword [esp], 2		; check if the string was provided
		jl		.noarg_exit

		mov		eax, [esp+8]		; get the address of the string
		mov		[straddr], eax		; move the address into the variable

		push	dword [straddr]		; push the string address to strlen
		call	strlen				; calculate the length
		add		esp, 4				; get rid of the string address in stack

		mov		[length], eax		; save the length

		shr		eax, 1				; divide the length by two
		mov		[range], eax		; left edge of the string to be printed
		mov		[range+4], eax		; the right edge

		test	word [length], 1	; check if the length is odd
		jnz		.is_odd				; skip the following operations if odd

		mov		ecx, [range]		; used as a counter
		dec		ecx					; decrease iterations for the character
.lp1:	PUTCHAR ` `					; print space
		loop	.lp1				; until ecx == 0

		xor		edi, edi			; clear edi
		mov		edi, [range]		; store the character's number
		mov		esi, [straddr]		; the address of the string start
		PUTCHAR byte [esi+edi-1]	; print the top character
		PUTCHAR newln				; new line

		mov		ebx, [range+4]		; move the right edge number to ebx
		inc		ebx					; increment ebx
		mov		[range+4], ebx		; save the number back in [range+4]
		jmp .lp2
.is_odd:							; increment initial range numbers
		mov		eax, [range]		; store the left side number in eax
		inc		eax					; increment it
		mov		[range], eax		; store in the left side number
		mov		[range+4], eax		; and the right side
.lp2:	xor		ecx, ecx
		mov		ecx, [range]		; the counter equals the left edge - 1
		dec		ecx					; one iteration less
		test	ecx, ecx			; if ecx == 0
		jz		.print_str			; skip space print

.llp2:	PUTCHAR ` `					; print a space
		loop	.llp2				; continue until ecx == 0
.print_str:
		mov		edi, [range]		; store the left edge in edi
		dec		edi					; decrement edi to get index
		xor		edx, edx			; zero edx
		mov		edx, [range+4]		; put the right edge
		sub		edx, [range]		; subtract the left edge from the right
		inc		edx					; increment
		mov		esi, [straddr]		; move string address to esi
		add		esi, edi			; add character's index
		PRINTSTR esi, edx			; print the string
		PUTCHAR newln				; put a new line character
		mov		eax, [range+4]		; write the right edge
		inc		eax					; increment it
		mov		[range+4], eax		; put it back
		mov		eax, [range]		; write the left edge
		dec		eax					; decrement it
		mov		[range], eax		; save

		test	eax, eax			; if the left edge is not zero
		jnz		.lp2				; continue

.exit:	FINISH 0					; no errors occurred
.noarg_exit:
		FINISH 1					; argc != 2

