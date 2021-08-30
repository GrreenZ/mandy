;;
;; Dithering pattern 
;; by Andrzej Borsuk
;;

	org	$ff00
	include patta.inc

black:
	ld	a,0
	ld	b,32
	next_black:
		ld (de),a
		inc de
	djnz next_black
	ret

main:
	call	fill		; DE now points to screen attributes
				; so let's use it
	ld	a,0
	ld	b,64
	next_attr:
		ld (de),a
		inc de
		inc a
	djnz next_attr
	
	call	black

	ld	b,8*3-4
	repeat:
	push	bc

		ld	hl,color
		ld	b,15
		next_color:
			ld a,(hl)
			ld (de),a
			inc hl
			inc de
		djnz next_color
		ld	b,16
		prev_color:
			ld a,(hl)
			ld (de),a
			dec hl
			inc de
		djnz prev_color
		ld (de),a
		inc de
	
	pop	bc
	djnz	repeat

	ret

end main
