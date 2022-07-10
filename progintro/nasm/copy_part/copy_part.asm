%include "kernel.inc"
extern str_to_int
extern strlen
global _start

;; The program reqires 3 parameters:
;; file1, file2, N. It copies N bytes
;; from file1 into cleaned file2.

; Workds faster then kernel
%macro FINISH 1
	mov	eax, 1
	mov	ebx, %1
	int	0x80
%endmacro

section .bss
N		resd 1		; number of bytes to copy
sour_s	resd 1		; source stream
dest_s	resd 1		; destination stream
buffer	resb 4096
bufsize	resd $-buffer

section .text
openrd	equ 0x000
openwr	equ 0x241
perm	equ 0666q	; permissions
read	equ 3
write	equ	4
open	equ 5
close	equ 6
base	equ "A"		; number system

_start:	cmp		dword [esp], 4
		jne		.err_arg

		mov		esi, [esp+16]
		push	esi
		call	strlen
		add		esp, 4

		push	dword base
		push	eax
		push	dword esi
		call	str_to_int
		add		esp, 12
		cmp		ecx, -1
		je		.err_parseint
		mov		[N], eax

		mov		esi, [esp+8]		; file1
		mov		edi, [esp+12]		; file2
		kernel	open, esi, openrd
		cmp		eax, -1
		je		.err_open
		mov		[sour_s], eax
		kernel	open, edi, openwr, perm
		cmp		eax, -1
		je		.err_open
		mov		[dest_s], eax

.lp:	kernel	read, dword [sour_s], buffer, bufsize
		cmp		eax, -1
		je		.err_read
		test	eax, eax			; if EOF,
		je		.lp_q				; nothing to read left

		mov		ecx, eax			; amount of read bytes
		cmp		[N], ecx
		jnl		.subN
		mov		ecx, [N]
		mov		dword [N], 0
		jmp		.dest_write
.subN:	sub		[N], ecx
.dest_write:
		kernel	write, dword [dest_s], buffer, ecx
		cmp		eax, -1
		je		.err_write
		cmp		dword [N], 0
		jg		.lp
.lp_q:	kernel	close, dword [sour_s]
		kernel	close, dword [dest_s]
		FINISH	0
.err_arg:
		FINISH	1
.err_parseint:
		FINISH	2
.err_open:
		FINISH	3
.err_read:
		FINISH	4
.err_write:
		FINISH	5
