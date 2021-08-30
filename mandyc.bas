# vi: ts=2 sw=2 expandtab autoindent
# 2021 by Andrzej Borsuk 

REM Load dithering pattern
for i=0 to 15
	read b : poke usr "a"+i,b
next i

REM Heat Map
dim a(16) : dim b(16) : dim c$(16)
for i=1 to 15
	read a(i),b(i),c$(i)
next i

REM MAIN
border 0:paper 0:ink 7
cls
for y=0 to 21
  for x=0 to 31

    @calculator:
    let xz=x*3.5/32-2.5
    let yz=y*2/22-1
    let xx=0
    let yy=0
    for i=0 to 14
      if xx*xx+yy*yy>4 then goto @plotter
      let xt=xx*xx-yy*yy+xz
      let yy=2*xx*yy+yz
      let xx=xt
    next i

    @plotter:
    print paper a(i);ink b(i);c$(i);

  next x
next y

@pattern:
REM  Dithering Pattern
# DATA 145,38,100,136,25,98,70,136
# DATA 219,175,118,159,189,110,245,219

# DATA 73,146,37,74,148,41,82,164
# DATA 219,183,111,222,189,123,246,237

DATA 0,0,60,60,60,60,0,0
DATA 0,126,126,126,126,126,126,0

@heatmap:
REM  Heat Map (colors 0,1,5,4,6,2,7)
DATA 0,1," ", 0,1,chr$(144), 0,1,chr$(145)
DATA 1,5," ", 1,5,chr$(144), 1,5,chr$(145)
DATA 5,4," ", 5,4,chr$(144), 5,4,chr$(145)
DATA 4,6," ", 4,6,chr$(144), 4,6,chr$(145)
DATA          6,2,chr$(144), 6,2,chr$(145)
DATA 2,7," "
