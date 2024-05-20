%include "kernel.inc"
global _start

;; The program reads lines from stdin
;; until EOF, then writes in binary file
;; result.dat the amount of read lines,
;; their summary length and the length of
;; the longest among them.

; Works faster then kernel
%macro FINISH 1		; exitcode
	mov eax, 1
	mov	ebx, %1
	int	0x80
%endmacro

section .data
file	db "result.dat", 0
newln_p	db 10, 0

section .bss
lcount	resd 1		; the three vars to save
llen	resd 1
longest	resd 1

fstream	resd 1
buffer	resb 4096
bufsize	equ $-buffer

section .text
newln	equ 10
stdin	equ	1
openwr	equ 0x241	; file mode for open
perm	equ 0666q	; permissions
read	equ 3
write	equ 4
open	equ 5
close	equ 6

_start:	kernel	read, stdin, buffer, bufsize
		cmp		eax, -1
		je		.err_read
		test	eax, eax
		je		.writeres

		xor		ecx, ecx		; line char counter
		xor		esi, esi		; buffer index
		dec		eax				; make eax index of the last char
.lp:	cmp		esi, eax
		jnle	.lp_q

		inc		ecx
		cmp		byte [buffer+esi], newln
		je		.exclude_nl
		cmp		esi, eax
		je		.recount
		jmp		.finally
.exclude_nl:
		dec		ecx
.recount:
		add		[llen], ecx
		inc		dword [lcount]
		cmp		ecx, [longest]
		jng		.clearecx
		mov		[longest], ecx
.clearecx:
		xor		ecx, ecx
.finally:
		inc		esi
		jmp		.lp
.lp_q:	
		jmp		_start
.writeres:
		kernel	open, file, openwr, perm
		cmp		eax, -1
		je		.err_open
		mov		[fstream], eax
		kernel	write, dword [fstream], lcount, 12	; write all three vars
		cmp		eax, -1
		je		.err_write

		kernel	write, stdin, newln_p, 1
		kernel	close, file
		FINISH	0
.err_read:
		FINISH	1
.err_open:
		FINISH	2
.err_write:
		FINISH	3
