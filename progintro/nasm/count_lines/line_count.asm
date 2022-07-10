%include "kernel.inc"
extern int_to_str
extern strlen
global _start

;; The program opens specified parameter
;; as file and counts the amount of lines
;; in the file, then prints this amount
;; in decimal form to stdin.

; Works faster then kernel
%macro FINISH 1		; exitcode
	mov eax, 1
	mov	ebx, %1
	int	0x80
%endmacro

section .data
newln_p	db 10, 0

section .bss
lncount	resd 1		; amount of lines
buffer	resb 4096
bufsize	equ $-buffer
file	resd 1		; file address
fstream	resd 1		; file descriptor
string	resb 33		; the number in ASCII form

section .text
base	equ "A"		; decimal number system
newln	equ	10
stdout	equ	1
O_RDONLY equ 0x000	; open file mode

read	equ 3		; syscall numbers
write	equ 4
open	equ 5
close	equ 6

_start:	cmp		dword [esp], 2
		jne		.err_arg
		mov		ebx, [esp+8]
		mov		[file], ebx

		kernel	open, dword [file], O_RDONLY
		cmp		eax, -1
		je		.err_open
		mov		[fstream], eax

		xor		ecx, ecx
.read_c:
		kernel	read, dword [fstream], buffer, bufsize
		test	eax, eax
		jle		.end_of_file
.count_c:
		cmp		byte [buffer+ecx], newln
		jne		.fin
		inc		dword [lncount]
.fin:	inc		ecx
		cmp		ecx, eax
		jl		.count_c

		jmp		.read_c
.end_of_file:
		cmp		eax, -1
		je		.err_read

		push	dword base			; base of the number system
		push	string				; string addr
		push	dword [lncount]		; number to parse
		call	int_to_str
		add		esp, 12
		
		push	string
		call	strlen
		add		esp, 4

		kernel	write, stdout, string, eax
		kernel	write, stdout, newln_p, 1
		kernel	close, dword [fstream]
		FINISH	0
.err_arg:
		FINISH	1
.err_open:
		FINISH	2
.err_read:
		FINISH	3
