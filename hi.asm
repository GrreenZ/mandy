;;
;; Ugliest assembly language example ever
;; committed by Andrzej Borsuk
;
;  Just testing if compiler works
;
;;

	ORG $ff00
	ld	a,'H'
	rst	16
	ld	a,'I'
	rst	16
	ld	a,'!'
	rst	16
	ld	a,13
	rst	16
	ld	bc,0
	ret
	END $ff00
