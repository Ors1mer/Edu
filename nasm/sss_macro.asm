%include "stud_io.inc"
global	_start

;; The macro creates area of memory of 4-byte elements,
;; where the first element equal to the first argument,
;; the rest of elements are bigger then the previous one
;; on the value of second argument. The length is the
;; third argument.

%macro	incarr 3		; start, step, size
		%assign n %1
		%rep %3
			dd n
			%assign n n+%2
		%endrep
%endmacro

section .data
incarr 2, 2, 20
