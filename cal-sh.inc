;;
;; Dump ZX Spectrum Calculator Stack and variables
;; Written by Andrzej Borsuk
;;

; don't forget to
; include cout.inc


; Newline
newline:
	ld	a,13
	rst	cout
	ret

; Show inline string$
mess:
	ex	(sp),hl
	ex	de,hl
	call	sh_s
	ex	de,hl
	ex	(sp),hl
	ret

; Show string$
; Enter:DE -> string$
; Exit:	DE -> next string$
;	A  =  '$'
sh_s:
	ld	a,(de)
	inc	de
	cp	'$'
	ret	z
	rst	cout
	jr	sh_s

; Show Memory (16bit)
; Enter:HL -> data
;	A  =  (HL)
sh_at:
	inc	hl
	ld	a,(hl)
	call	cout_hex
	dec	hl
	ld	a,(hl)
	call	cout_hex
	ret


; Show float as HEX
; Enter:HL -> fp_number
; Exit: HL -> next fp_number

sh_n:
	push	bc
	ld	b,4
sh_n1:
	ld	a,(hl)
	call	cout_hex
	inc	hl
	ld	a,'.'
	rst	cout
	djnz	sh_n1

	pop	bc

	ld	a,(hl)
	call	cout_hex
	inc	hl
	ret

; Show STK top as DEC
sh_top:
	push	af
	push	bc
	push	de
	push	hl
	db	fbegin
	db	fdup
	db	fend
	call	PRINT_FP
	pop	hl
	pop	de
	pop	bc
	pop	af
	ret

sh_c0: db	$14,1,' STK $:$ MEM $ BREG $ ',$14,0,13,'$'
	
; FUNCTION SH_CALC
; Show calculator header
; and it's system variables
; ENTER:-
; EXIT: DE = cal_stk
;	A  = '$'

sh_calc:
	ld	de,sh_c0

	call	sh_s
	ld	hl,STKBOT
	call	sh_at

	call	sh_s
	ld	hl,STKEND
	call	sh_at

	call	sh_s
	ld	hl,MEM
	call	sh_at

	call	sh_s
	ld	a,(BREG)
	call	cout_hex

	call	sh_s
	ret
	
; FUNCTION SH_STK
; Show calculator stack
; ENTER:-
; EXIT: A=?
; 	HL=?
;	DE=?

sh_stk0:
	db	'stk:',13,'$'
sh_stk:
	ld	de,sh_stk0
	call	sh_s

	ld	hl,(STKBOT)
	ld	de,(STKEND)

sh_stk1:
	ld	a,l
	cp	e
	jr	nz,sh_stk2

	ld	a,h
	cp	d
	ret	z

sh_stk2:
	call	sh_n
	ld	a,13
	rst	cout
	jr	sh_stk1

	ret


; FUNCTION SH_MEM
; Show calculator stack
; ENTER:B=how many?
; EXIT: A=?
;	B=0
; 	HL=?
;	DE=?

sh_mem0:
	db	'mem:',13,'$'
sh_mem5:	; shortcut
	ld	b,5
sh_mem:
	push	de
	ld	de,sh_mem0
	call	sh_s
	pop	de

	ld	hl,(MEM)
sh_mem1:
	call	sh_n
	ld	a,13
	rst	cout
	djnz	sh_mem1

	ret

