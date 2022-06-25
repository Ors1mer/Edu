%include "stud_io.inc"
global _start

;; The program reads lines and writes "OK"
;; until EOF

section .text
newl	equ 10
EOF		equ -1

_start: xor eax, eax
read_c:
		GETCHAR
		cmp	eax, newl
		je	print_msg

		cmp eax, EOF
		je	exit

		jmp read_c
print_msg:
		PRINT "OK"
		PUTCHAR newl
		jmp read_c
exit:
		PUTCHAR newl
		FINISH 0
