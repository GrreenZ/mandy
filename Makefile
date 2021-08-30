#
# Semi universal Makefile for ZX Spectrum projects
# by Andrzej Borsuk
#

# this will select machine and force autloading
# just in case it's disabled in config
# Useful for testing
run:	mandy.tap
	fuse --no-confirm-actions \
		-m 48 --rom-48 48.rom --auto-load $< >/dev/null

# Primary binaries
all:	mandy.tap mandy1.tap mandy0.tap
all:	cal-hello.tap hi.tap hello.tap
clean:
	rm -f *.tap

# Additional deps
mandy.tap:	cal.inc cout.inc patta.inc
cal-hello.tap:	cal-hello.asm cal-sh.inc cal.inc cout.inc
patta.tap:	patta.asm patta.inc

mand-ref.tap:	mand-ref.bas
	zmakebas -a10 -n 'Mand REF' -o $@ $<
	

# HOWTO compile this stuff:
.SUFFIXES: .asm .bas .as .tap

# Create TAPe for basic program
.bas.tap:
	zmakebas -l -a10 -i10 -n $* -o $*.tap $*.bas
	listbasic $*.tap

# Compile ASM program (also attach loader)
.asm.tap:
	pasmo --tapbas $*.asm $*.tap
	listbasic $*.tap

# Complile ASM library (?) - no loader
.as.tap:
	pasmo --tap $*.asm $*.tap
