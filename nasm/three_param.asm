global _start

;; The program accepts any amount of command line
;; parameters, but finishes successfully only if
;; three parameters given.

%macro FINISH 1		; exitcode
					; no sense in pushing as the program ends
	mov		eax, 1	; syscall code for _exit
	mov		ebx, %1	; write exitcode
	int		0x80	; do system call
%endmacro

section .text
_start:	cmp	dword [esp], 4	; check the param amount (including program name)
		jne	err_exit
exit:	FINISH 0
err_exit:
		FINISH 1
