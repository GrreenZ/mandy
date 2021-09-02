#
# Semi universal Makefile for CP/M and ZX Spectrum
# 2021 by Andrzej Borsuk
#
                                                                                 
#############################################################################
#
# CP/M TURBO Pascal
#

.SUFFIXES: .pas .com

.pas.com:
	turbo $*


#############################################################################
#
# CP/M BASIC (BASCOM)
#

.SUFFIXES: .bas .rel .com                                                        

.bas.rel:                                                                        
	bascom.com $*,$*=$*/o/z                                                  
.rel.com:                                                                        
	l80.com $*,$*/n/e                                                        
	chmod a+x $*.com                    

#############################################################################
#
# ZX Spectrum BASIC
#

.SUFFIXES: .bas .tap

# Create TAPe for basic program
.bas.tap:
	zmakebas -l -a10 -i10 -n $* -o $*.tap $*.bas
	listbasic $*.tap

#############################################################################
#
# ZX Spectrum Assembler 
#

.SUFFIXES: .asm .as .tap

# Compile ASM program with loader
.asm.tap:
	pasmo --tapbas $*.asm $*.tap
	listbasic $*.tap

# Complile ASM library without loader
.as.tap:
	pasmo --tap $*.asm $*.tap

#
# EOF
#
#############################################################################
