#
# Semi universal Makefile for ZX Spectrum projects
# by Andrzej Borsuk
#

include rules.mk

ALL  =	mandp.com
ALL +=	mandy.tap mandy1.tap mandy0.tap
ALL +=	cal-hello.tap hi.tap hello.tap


# Primary binaries
all:	$(ALL)
clean:
	rm -f $(ALL)
distclean:	clean
	./pkg remove all
	rm .env

# CP/M compilers
mandp.com: turbo.com

turbo.com:
	./pkg install turbo

# this will select machine and force autloading
# just in case it's disabled in config
# Useful for testing
run:	mandy.tap
	fuse --no-confirm-actions \
		-m 48 --rom-48 48.rom --auto-load $< >/dev/null

# Additional deps
mandy.tap:	cal.inc cout.inc patta.inc
cal-hello.tap:	cal-hello.asm cal-sh.inc cal.inc cout.inc
patta.tap:	patta.asm patta.inc

mand-ref.tap:	mand-ref.bas
	zmakebas -a10 -n 'Mand REF' -o $@ $<
	

