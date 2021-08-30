REM Load dithering pattern
REM 2021 by Andrzej Borsuk
for i=0 to 15
	read b : poke usr "a"+i,b
next i

REM Heat Map
dim a(16) : dim b(16) : dim c$(16)
for i=1 to 16
	read a(i),b(i),c$(i)
next i

@main:
REM Show Pattern
for l=1 to 10
  for i=1 to 16
	print paper a(i);ink b(i);c$(i);
  next i
  print
next l


@pattern:
REM  Dithering Pattern
# DATA 145,38,100,136,25,98,70,136
# DATA 219,175,118,159,189,110,245,219
REM  "a" .___.___
DATA BIN 10010001
DATA BIN 00100110
DATA BIN 01100100
DATA BIN 10001000
DATA BIN 00011001
DATA BIN 01100010
DATA BIN 01000110
DATA BIN 10001000
REM  "b" .___.___
DATA BIN 11011011
DATA BIN 10101111
DATA BIN 01110110
DATA BIN 10011111
DATA BIN 10111101
DATA BIN 01101110
DATA BIN 11110101
DATA BIN 11011011

@heatmap:
REM  Heat Map (colors 0,1,5,4,6,2,7)
DATA 0,1," ", 0,1,chr$(144), 0,1,chr$(145)
DATA 1,5," ", 1,5,chr$(144), 1,5,chr$(145)
DATA 5,4," ", 5,4,chr$(144), 5,4,chr$(145)
DATA 4,6," ", 4,6,chr$(144), 4,6,chr$(145)
DATA 6,2," ", 6,2,chr$(144), 6,2,chr$(145)
DATA 2,7," "
