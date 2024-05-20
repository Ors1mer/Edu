;; addsubmul.asm
%include "stud_io.inc"
global	_start

extern	str_to_int
extern	int_to_str
extern	read_num
extern	print_str

section .data
num_str	times 11 db 0
num_len	equ	$-num_str

section .bss
num1	resd 1
num2	resd 1

section .text
newln	equ 10
EOF		equ -1
_start:	xor		ebx, ebx		; state variable, decides what to do next
		; Read num
getnum:	push	dword num_len
		push	dword num_str
		call	read_num
		add		esp, 8
		; Error check
		test	ebx, ebx
		jne		errnum2
errnum1:
		cmp		al, " "
		jne		err_input
		jmp		savenum
errnum2:
		cmp		al, newln
		je		savenum
		cmp		al, EOF
		je		savenum
		jmp		err_input
savenum:
		push	ecx
		push	dword num_str
		call	str_to_int
		add		esp, 8

		test	ebx, ebx		; deside which num is to save
		jne		casenum2
casenum1:
		mov		[num1], eax
		inc		ebx
		jmp		getnum
casenum2:
		mov		[num2], eax
		jmp		addnum

		; Error handling
err_input:
		cmp		eax, -2			; if eax == -2,
		je		err_size		; then the number is too big,
		jmp		err				; else bad character
err_size:
		PRINT	"The number is too big!"
		PUTCHAR	newln
		jmp		err_exit
err:	PRINT	"Couldn't understand character '"
		PUTCHAR	al
		PUTCHAR "'"
		PUTCHAR	newln
		jmp		err_exit

		; Do calculations
addnum:	mov		eax, [num1]
		add		eax, [num2]
		jmp		print
subnum:	mov		eax, [num1]
		sub		eax, [num2]
		jmp		print
mulnum:	mov		eax, [num1]
		mul		dword [num2]
		jmp		print
print:	push	dword num_str	; string address
		push	eax				; the integer
		call	int_to_str		; write eax to num_str
		add		esp, 4			; remove eax from the stack
		call	print_str		; print sum
		PUTCHAR	newln

		xor		ecx, ecx		; used as counter
emp_c:	cmp		ecx, num_len
		je		nextst
		mov		[num_str+ecx], byte 0
		inc		ecx
		jmp		emp_c

nextst:	inc		ebx
		cmp		ebx, 2			; decide, which action is next
		je		subnum
		cmp		ebx, 3
		je		mulnum
		jmp		exit

err_exit:
		FINISH	1
exit:	FINISH	0
