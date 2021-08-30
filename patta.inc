;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Dithering pattern 
;; by Andrzej Borsuk
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;  Heat Map (HSV 240deg -> 0deg)
;  HSV (HSL) Color model
;
;  Angle:              Color mapping
;         0                 2
;  300    R    60      3    R    6
;     m .---. y         m .---. y
;      |  +  |           |  +  |
;     B '---' G         B '---' G
;  240    c    120     1    c    4
;        180                5      
; 
; Selected colors: 0,1,5,4,6,2 + 7
;

	; ALIGN to nibble
	; (lower 4 bits of "color" table are always 0)
	ds	($+$0f&$fff0)-$
color:
;	db 000o,001o,011o,015o
;	db 055o,054o,044o,046o
;	db 066o,062o,022o,122o
;	db 126o,166o,177o,375o

	; simmilar to above but some colors are stretched
	db 000o,      001o,      011o,      015o
	db 055o,      054o,054o, 044o,044o, 046o
	db 046o,      062o,      022o,022o, 122o
	db 126o,      166o,      177o,      375o

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Get heat level
; lower 4 bits of color table are always 0
;
; ENTER:A  = index
; EXIT: A  = heat level value
;       HL = heat level ptr

heat:	REPT 1
	ld	hl,color
	or	l
	ld	l,a
	ld	a,(hl)
	ret
ENDM

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Pattern generator makes use of ZX Spectrum screen memory layout
; Screen is divided in 3 blocks, each contains 32*8 (256) characters.
; Each 256 bytes represent single scanline for all characters in block.

; There are three possible pattern styles with 1,2,4 "pixel" size:
PATSIZE	EQU	GRAIN

; PAT4 checker pattern
IF PATSIZE=4
UPPER	EQU	$0f	; upper half
LOWER	EQU	$f0	; lower half
PSIZE	EQU	$0400	; repeat 4*256 times
PFILL	EQU	$1000	; 2*$800 (2/3 of screen) to populate
ENDIF

; PAT2 2px checker pattern
IF PATSIZE=2
UPPER	EQU	$33	; upper half
LOWER	EQU	$cc	; lower half
PSIZE	EQU	$0200	; repeat 4*256 times
PFILL	EQU	$1400	; 2*$800 (2/3 scr) + $400 (missing) to populate
ENDIF

; PAT1 1px checker pattern - classic dithering
IF PATSIZE=1
UPPER	EQU	$55	; upper half
LOWER	EQU	$aa	; lower half
PSIZE	EQU	$0100	; repeat 4*256 times
PFILL	EQU	$1600	; 2*$800 (2/3 scr) + $600 (missing) to populate
ENDIF

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Pattern generator
; ENTER:
; EXIT:	AF = ?
;	BC = ?
;	DE = Screen Memory (color attributes)
;	HL = ?
;

fill:	REPT 1

	; prepare pattern on 1/3 screen area
	ld	hl,$4000	; src (screen memory)
	ld	de,$4001	; dst
	push	hl		; save for "populate" part

	; upper half of the checker (plus 1 for next part)
	ld	a,UPPER
	ld	(hl),a		; write pattern
	ld	bc,PSIZE	; repeat PSIZE times
	ldir			; distribute pattern

	; lower half of the checker
	ld	a,LOWER
	ld	(hl),a		; write pattern (1st byte)
	ld	bc,PSIZE-1	; repeat PSIZE-1 times
	ldir			; distribute pattern

	; populate rest of the screen
	pop	hl		; move src to begin of the screen
	ld	bc,PFILL	; missing bytes to fill
	ldir

	ret
ENDM

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Fill color space with one color
; This proc is intended to be executed after fill
; ENTER:A  = color
;	DE = Screen Memory (color attributes)
; EXIT: A  = color
;	B  = 0
;	DE = ?

fill_c:REPT 1
	LOCAL fill_next
	out (256),a
	ld b,0	; 32*24/3=256
	fill_next:
		ld (de),a
		inc de
		ld (de),a
		inc de
		ld (de),a
		inc de
	djnz fill_next
	jp   $229b		; set-border rom call
ENDM


