%include "stud_io.inc"
global _start

;; The program reads lines from stdin
;; until EOF, and for each written line
;; prints either YES or NO if bracket
;; balance is present or not respectively

section .text
newln	equ 10
EOF		equ -1
open_b	equ	"("
close_b	equ ")"

_start:	xor eax, eax	; char from stdin
		xor edx, edx	; amount of "("
		xor ebx, ebx	; amount of ")"
read_c:	GETCHAR
		cmp	eax, EOF	; if EOF,
		je	check_equal	; print answer for the line and exit

		cmp	eax, newln	; if newline,
		je	check_equal	; print answer & move to _start

		cmp	eax, open_b	; if "(",
		je	inc_edx		; increase it's count
		cmp	eax, close_b
		je	inc_ebx
		jmp	check_balance
inc_edx:
		inc	edx
		jmp	check_balance
inc_ebx:
		inc	ebx
		jmp	check_balance
check_balance:
		cmp	edx, ebx
		jl	bad_balance
		jmp read_c
bad_balance:
		mov ecx, 1		; shows that string unbalanced
		jmp	read_c
check_equal:
		cmp ecx, 1		; if string was marked as unbalanced
		je print_no	

		cmp	edx, ebx
		je	print_yes
		jmp	print_no

print_yes:
		PRINT "YES"
		jmp continue
print_no:
		xor ecx, ecx
		PRINT "NO"
		jmp continue
continue:
		PUTCHAR newln
		cmp	eax, EOF	; if EOF,
		je	exit		; end the program
		jmp	_start		; else start reading another line
exit:	FINISH 0
