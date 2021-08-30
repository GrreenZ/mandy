;;
;; ZX Spectrum Calculator Opcodes
;; Desctiption from ROM Assembly Listing
;;
;; Opcode names are inspired by
;; https://sinclair.wiki.zxnet.co.uk/wiki/X80
;;
;; Mashed together by Andrzej Borsuk
;; Feel free to do whatewer you want with this
;;

fbegin	EQU	$EF		; RST 28

; some system variables
STKBOT	EQU	$5c63	; 23651
STKEND	EQU	$5c65	; 23653
BREG	EQU	$5c67	; 23655
MEM	EQU	$5c68	; 23656

; Useful ROM calls
A_TO_STK	EQU	$2d28
BC_TO_STK	EQU	$2d2b
STK_TO_A	EQU	$2314
STK_TO_BC	EQU	$2307

PRINT_FP	EQU	$2DE3
FP_TO_A		EQU	$2DD5
FP_TO_BC	EQU	$2DA2

;; tbl-addrs

;op		code		  code addr   description
fjpt	EQU	$00		; $00 $368F - jump-true
fxch	EQU	$01		; $01 $343C - exchange
fdel	EQU	$02		; $02 $33A1 - delete

;   True binary operations.

fsub	EQU	$03		; $03 $300F - subtract
fmul	EQU	$04		; $04 $30CA - multiply
fdiv	EQU	$05		; $05 $31AF - division
fpow	EQU	$06		; $06 $3851 - to-power

for	EQU	$07		; $07 $351B - or
fand	EQU	$08		; $08 $3524 - no-&-no

fle	EQU	$09		; $09 $353B - no-l-eql
fge	EQU	$0A		; $0A $353B - no-gr-eql
fne	EQU	$0B		; $0B $353B - nos-neql
fgt	EQU	$0C		; $0C $353B - no-grtr
flt	EQU	$0D		; $0D $353B - no-less
feq	EQU	$0E		; $0E $353B - nos-eql

fadd	EQU	$0F		; $0F $3014 - addition

fands	EQU	$10		; $10 $352D - str-&-no
fles	EQU	$11		; $11 $353B - str-l-eql
fges	EQU	$12		; $12 $353B - str-gr-eql
fnes	EQU	$13		; $13 $353B - strs-neql
fgts	EQU	$14		; $14 $353B - str-grtr
flts	EQU	$15		; $15 $353B - str-less
feqs	EQU	$16		; $16 $353B - strs-eql
fadds	EQU	$17		; $17 $359C - strs-add

;   Unary follow.

fvals	EQU	$18		; $18 $35DE - val$
fusrs	EQU	$19		; $19 $34BC - usr-$
fread	EQU	$1A		; $1A $3645 - read-in
fneg	EQU	$1B		; $1B $346E - negate

fasc	EQU	$1C		; $1C $3669 - code
fval	EQU	$1D		; $1D $35DE - val
flen	EQU	$1E		; $1E $3674 - len
fsin	EQU	$1F		; $1F $37B5 - sin
fcos	EQU	$20		; $20 $37AA - cos
ftan	EQU	$21		; $21 $37DA - tan
fasn	EQU	$22		; $22 $3833 - asn
facs	EQU	$23		; $23 $3843 - acs
fatn	EQU	$24		; $24 $37E2 - atn
fln	EQU	$25		; $25 $3713 - ln
fexp	EQU	$26		; $26 $36C4 - exp
fint	EQU	$27		; $27 $36AF - int
fsqr	EQU	$28		; $28 $384A - sqr
fsgn	EQU	$29		; $29 $3492 - sgn
fabs	EQU	$2A		; $2A $346A - abs
fpeek	EQU	$2B		; $2B $34AC - peek
fin	EQU	$2C		; $2C $34A5 - in
fusr	EQU	$2D		; $2D $34B3 - usr-no
fstrs	EQU	$2E		; $2E $361F - str$
fchrs	EQU	$2F		; $2F $35C9 - chrs
fnot	EQU	$30		; $30 $3501 - not

;   End of true unary.

fdup	EQU	$31		; $31 $33C0 - duplicate
fmod	EQU	$32		; $32 $36A0 - n-mod-m
fjp	EQU	$33		; $33 $3686 - jump
fstk	EQU	$34		; $34 $33C6 - stk-data
fdjnz	EQU	$35		; $35 $367A - dec-jr-nz
flz	EQU	$36		; $36 $3506 - less-0
fgz	EQU	$37		; $37 $34F9 - greater-0
fend	EQU	$38		; $38 $369B - end-calc
fget	EQU	$39		; $39 $3783 - get-argt
ftrn	EQU	$3A		; $3A $3214 - truncate
fsgl	EQU	$3B		; $3B $33A2 - fp-calc-2
fetof	EQU	$3C		; $3C $2D4F - e-to-fp
frstk	EQU	$3D		; $3D $3297 - re-stack

; Variables and Constants

fstk0		EQU	$A0		; Store const (0)
fstk1		EQU	$A1		; Store const (1)
fstk1_2		EQU	$A2		; Store const (1/2)
fstkpi_2	EQU	$A3		; Store const (pi/2)
fstk10		EQU	$A4		; Store const (10)

fsetm		EQU	$C0		; Store in MEM + X
fsetm0		EQU	$C0		; Store in MEM 0
fsetm1		EQU	$C1		; Store in MEM 1
fsetm2		EQU	$C2		; Store in MEM 2
fsetm3		EQU	$C3		; Store in MEM 3
fsetm4		EQU	$C4		; Store in MEM 4
fsetm5		EQU	$C5		; Store in MEM 5

fgetm		EQU	$E0		; Get from MEM + X (fgetm+4)
fgetm0		EQU	$E0		; Get from MEM 0
fgetm1		EQU	$E1		; Get from MEM 1
fgetm2		EQU	$E2		; Get from MEM 2
fgetm3		EQU	$E3		; Get from MEM 3
fgetm4		EQU	$E4		; Get from MEM 4
fgetm5		EQU	$E5		; Get from MEM 5


