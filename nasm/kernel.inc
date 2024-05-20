;; Macro for system calls
;; Follows CDECL convencion
;; Works only on Linux
;; Accepts number of syscall & required parameters

%macro kernel 1-*
	%if %0 > 1
		push	ebx
		%if %0 > 4
			push	esi
			push	edi
			push	ebp
		%endif
	%endif
	%rep %0
		%rotate -1
					push dword %1
	%endrep
							pop	eax
	%if %0 > 1
							pop	ebx
		%if %0 > 2
							pop	ecx
			%if %0 > 3
							pop	edx
				%if %0 > 4
							pop	esi
					%if %0 > 5
							pop	edi
						%if %0 > 6
							pop	ebp
							%if %0 > 7
								%error "Can't do syscall with 7+ params"
							%endif
						%endif
					%endif
				%endif
			%endif
		%endif
	%endif
	
	int 0x80
	mov	ecx, eax
	and	ecx, 0x0fffff000
	cmp	ecx, 0x0fffff000
	jne	%%no_err
	mov	ecx, eax
	neg	ecx
	mov	eax, -1
	jmp	short %%quit
%%no_err:
	xor	ecx, ecx
%%quit:
	%if %0 > 1
		%if %0 > 4
			pop	ebp
			pop	edi
			pop	esi
		%endif
			pop ebx
	%endif
%endmacro
