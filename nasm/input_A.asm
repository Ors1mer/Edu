%include "stud_io.inc"
global _start

;; The program prints YES if the input is 'A', in any other case - NO

section	.text
_start: xor		al, al
		GETCHAR
		cmp		al, 65
		je		yes   ; print yes if 'A'
		PRINT	"NO"  ; else print no
		PUTCHAR	10
		FINISH	0
yes:	PRINT	"YES"
		PUTCHAR	10
		FINISH	0
