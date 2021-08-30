;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
;;  CP/M Console IO macro
;;  Adapted to ZX Spectrum
;;  Copyright (c) 2021 Andrzej Borsuk
;;
;;  cout_str prints stringz
;;  cout_chr prints single character
;;  cout_hex prints hex number
;;

cout	equ	16	; (usage: rst cout)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Console output HEX
; Enter: A = 8 bit value
; Exit:  BDOS stuff
;
cout_hex:
cout_8h:
	push	af
	rrca			; swap nibbles in	4
	rrca			; ...			3
	rrca			; ... 			2
	rrca			; ... 			1
	call	cout_4h		; print 1st digit
	pop	af		; and again ...
	; call  cout_4h
	; ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Console output HEX
; Enter: A = 4 bit value to print (single digit)
; Exit:  BDOS stuff
;
cout_4h:
	and	$0f		; mask data
	add	a,'0'		; convert to ascii
	cp	':'		; more than "0".."9"?
	jr	c,cout_chr	; 
	add	a,'A'-':'	; use letters
	; jr	cout_chr

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Console output
; Enter: A = Single character
; Exit:  ???
;
cout_chr:
	rst	16
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Console output inline stringz
; Enter: PC
; Exit:  A = 0
;	 PC=PC+stringz
;
cout_msg:
	ex	(sp),hl
	call	cout_str
	ex	(sp),hl
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Console output stringz
; Enter: HL
; Exit:  HL -> string end
;	 A = 0
;
cout_str:
	ld	a,(hl)
	inc	hl
	cp	0
	ret	z
	rst	16
	jr	cout_str

;
; EOF
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
