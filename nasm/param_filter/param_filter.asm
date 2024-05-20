global _start
extern strlen
extern flt4

;; The program accepts any amount of parameters
;; and then prints those parameters that satisfy
;; the condition of fltN, where N - number of the
;; filtering function (1 through 4)

%macro FINISH 1
	mov eax, 1
	mov	ebx, %1
	int	0x80
%endmacro

%macro PRINTSTR 2	; address and length
	push	eax
	push	ebx
	push	ecx
	push	edx

	mov		eax, 4	; write syscall
	mov		ebx, 1	; stdout
	mov		ecx, %1	; address
	mov		edx, %2	; length
	int		0x80

	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
%endmacro

section .data
space	db " ", 0
newln	db 10, 0

section .text
_start:	mov		edi, 2				; nth parameter

		cmp		dword [esp], 1		; if there are parameters
		jne		lp					; start filtering loop
		FINISH	0					; else finish program

lp:		cmp		edi, [esp]
		jg		lp_q
		mov		esi, [esp+4*edi]	; parameter address

		push	esi
		call	flt4				; returns eax as a bool value
		add		esp, 4

		test	eax, eax			; if eax != 0, parameter is good
		je		finally

		push	esi
		call	strlen
		add		esp, 4

		mov		ebp, eax			; it is forbidden to pass length in eax
		PRINTSTR esi, ebp
		PRINTSTR space, 1
finally:
		inc		edi
		jmp		lp
lp_q:	PRINTSTR newln, 1
		FINISH	0
