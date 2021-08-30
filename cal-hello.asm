;;
;; ZX Spectrum Calculator API
;; playing ground
;;
;; Inteded to be Hello World kind of example
;; 2021 by Andrzej Borsuk

	ORG	$8000

	jp	main
	include cout.inc
	include cal.inc
	include cal-sh.inc

; My own MEM
MX:
	db	0,0,0,0,0
	db	0,0,1,0,0
	db	0,0,2,0,0
	db	0,0,3,0,0
	db	0,0,4,0,0
	db	0,0,5,0,0
	ds	4*5;		; and more :)


main:

	; set own MX location
	ld	hl,(MEM)
	push	hl
	ld	hl,MX
	ld	(MEM),hl

	db	fbegin
	db	fstkpi_2	; pi/2
	db	fdup		; pi/2
	db	fadd		; +		(pi)

	db	fstk10		; 1 or 10
	db	fend
	call	sh_calc
	call	sh_stk

	db	fbegin
	db	fsub
	db	fgz		; -
	db	fend
	call	sh_calc
	call	sh_stk

	; Print stack top
	; call	PRINT_FP ; zero on stack
	; ld	a,13
	; rst	cout

	; Restore original MEM
	pop	hl
	ld	(MEM),hl

	ret
end main
