%include "kernel.inc"
extern strlen
global _start

;; The program opens the first parameter
;; as file and writes into it the
;; rest of the parameters separated
;; by space 10 times in 10 lines.

; Works faster then kernel
%macro FINISH 1		; exitcode
	mov eax, 1
	mov	ebx, %1
	int	0x80
%endmacro

section .bss
file	resd 1		; filename address
fstream	resd 1		; file descriptor
argc	resd 1		; argument count
string	resb 512	; the string made from parameters
slen	resd 1

section .text
newln	equ	10
stdout	equ	1
openwr	equ 0x241	; open file mode
perm	equ 0666q	; permission to read & write for all

write	equ 4		; syscall numbers
open	equ 5
close	equ 6

_start:	mov		ebx, [esp]
		mov		[argc], ebx
		cmp		dword [argc], 3
		jnge	.err_arg
		mov		ebx, [esp+8]
		mov		[file], ebx

		; Form the string to write
		mov		ebx, [argc]
		lea		eax, [esp+4*ebx]
		mov		ebx, eax			; pointer to the last arg
		lea		ebp, [esp+12]		; pointer to the first arg
		mov		esi, [ebp]			; addr of the first arg
		mov		edi, string			; the string index
		xor		ecx, ecx			; arg's string index
.lp1:	cmp		byte [esi+ecx], 0	; if end,
		je		.lp1_q				; ...writing of the arg is done
		mov		al, [esi+ecx]		; getchar from arg string
		mov		[edi], al			; store in the memory string
		inc		ecx
		inc		edi
		jmp		.lp1
.lp1_q:	mov		byte [edi], " "
		inc		edi
		xor		ecx, ecx
		add		ebp, 4
		cmp		ebp, ebx
		jnle	.lp2_q
		mov		esi, [ebp]
		jmp		.lp1
.lp2_q:
		mov		byte [edi-1], newln
		mov		byte [edi], 0

		push	string
		call	strlen
		add		esp, 4
		mov		[slen], eax

		; Write string 10 times
		kernel	open, dword [file], openwr, perm
		cmp		eax, -1
		je		.err_open
		mov		[fstream], eax

		mov		esi, 10			; number of iterations of lp3
.lp3:	kernel	write, dword [fstream], string, [slen]
		cmp		eax, -1
		je		.err_write

		dec		esi
		test	esi, esi
		jnle	short .lp3
.lp3_q:	kernel	close, dword [fstream]
		FINISH	0
.err_arg:
		FINISH	1
.err_open:
		FINISH	2
.err_write:
		FINISH	3
