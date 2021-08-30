;;
;; Mandelbort Fractal
;; Copyright 2021 by Andrzej Borsuk
;;
;; This is a very early version
;; more to come soon

	ORG	$8000

; fpu memory
m0:	db	0,0,20,0,0	; X
m1:	db	0,0,10,0,0	; Y
m2:	db	0,0,0,0,0	; xz	- scaled x
m3:	db	0,0,0,0,0	; yz	- scaled y
m4:	db	0,0,0,0,0	; xx
m5:	db	0,0,0,0,0	; yy
m6:	db	0,0,0,0,0	; xx*xx
m7:	db	0,0,0,0,0	; yy*yy
m8:	db	0,0,4,0,0	; 4

; fpu register
x	equ	0
y	equ	1
xz	equ	2
yz	equ	3
xx	equ	4
yy	equ	5
xx2	equ	6
yy2	equ	7
c4	equ	8

; byte ptr
var_x	equ	m0+2
var_y	equ	m1+2

GRAIN	EQU	4	; pattern grain must be definied before include

	include	cout.inc
	include	cal.inc
	include	cal-sh.inc
	include patta.inc

FDUMP:	MACRO
	db	fend
	push	af
	call	newline
	ld	a,'['
	rst	cout
	call	sh_top
	ld	a,']'
	rst	cout
	call	newline
	pop	af
	db	fbegin
ENDM

mandi:
	db	fbegin

	; xz = x*3.5/32-2.5
	db	fgetm+x			; x
	db	fstk,$2d,$60		; 3.5/32
	db	fmul			; *
	db	fstk,$32,$a0		; -2.5
	db	fadd			; +
	db	fsetm+xz		; set xz
	db	fdel

	; yz = y*2/22-1
	db	fgetm+y			; y
	db	fstk
	db	$ed,$3a,$2e,$8b,$a3	; 2/22
	db	fmul			; *
	db	fstk1			; 1
	db	fsub			; -
	db	fsetm+yz		; set yz
	db	fdel

	; xx = yy = 0
	db	fstk0			; 0
	db	fsetm+xx		; set xx
	db	fsetm+yy		; set yy
	db	fdel
	
	db	fend

	; repeat 15
	ld	b,15
	next:
	push	bc

		; xx*xx+yy*yy>4
		db fbegin

		db fgetm+xx		; xx
		db fdup			; xx
		db fmul			; *
		db fsetm+xx2		; set xx2

		db fgetm+yy		; yy
		db fdup			; yy
		db fmul			; *
		db fsetm+yy2		; set xx2

		db fadd			; +

		db fgetm+c4		; 4
		db fsub			; -
		db fgz			; >
		db fend

		call	STK_TO_A
		cp	1
		jr	z, display

		db fbegin
		; xt = xx*xx - yy*yy + xz
		db fgetm+xx2		; xx*xx
		db fgetm+yy2		; yy*yy
		db fsub			; -
		db fgetm+xz		; xz
		db fadd			; +		(xt)

		; yy = 2 * xx * yy + yz
		db fgetm+xx		; xx
		db fgetm+yy		; yy
		db fmul			; *		(xx*yy)
		db fdup			; xx*yy
		db fadd			; +		(xx*yy)+(xx*yy)
		db fgetm+yz		; yz
		db fadd			; +
		db fsetm+yy		; set yy
		db fdel

		; xx = xt
		db fsetm+xx		; set xx	(xt)
		db fdel

		db fend
		
	pop	bc
	djnz	next
	push	bc

	display:

	ld	a,14
	pop	bc
	sub	b		; I=

	ret

attr:	db $00,$00

main:
	; fill screen memory
	call	fill		; dithering pattern
	ld	(attr),de	; save for later
	ld	a,0		; fill color
	call	fill_c

	; Set own MEM location
	ld	hl,(MEM)
	push	hl
	ld	hl,m0
	ld	(MEM),hl

	ld	b,22
	next_y:
	push	bc

		ld	a,22
		sub	b
		ld	(var_y),a

		ld	b,32
		next_x:
		push	bc

			ld	a,32
			sub	b
			ld	(var_x),a

			call	mandi

			; add	a,' '
			; rst	cout

			call	heat
			ld	de,(attr)
			ld	(de),a
			inc	de
			ld	(attr),de

		pop	bc
		djnz	next_x

		; call	newline

	pop	bc
	djnz	next_y


	; Restore original MEM
	pop	hl
	ld	(MEM),hl
	ret
end main
