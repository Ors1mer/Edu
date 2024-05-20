%include "stud_io.inc"
global _start

;; The macro does jump to a label which
;; number in argument list corresponds to
;; value in EAX. If no correspondings,
;; does nothing.

%macro labeljmp 1-*		; accepts any amount of labels
	test	eax, eax	; check if eax corresponds requirements
	jle		%%quit
	cmp		eax, %0
	jg		%%quit
	section .data
	lbarr				; reserve memory for labels
	%rep %0				; fill memory with labels
		dd %1
		%rotate 1
	%endrep
	section .text
	jmp	[lbarr+4*eax-4]	; jump to needed label
%%quit:
%endmacro

section .text
_start:	mov eax, 2
		labeljmp lb1, lb2, lb3, lb4
		PRINT "NONE"
		jmp	exit
lb1:	mov	eax, "1"
		jmp exit
lb2:	mov	eax, "2"
		jmp exit
lb3:	mov	eax, "3"
		jmp exit
lb4:	mov eax, "4"
		jmp exit
exit:	PUTCHAR al
		PUTCHAR 10
		FINISH	0
