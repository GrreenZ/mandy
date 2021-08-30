1 REM Mandelbrot set
2 REM Matt Heffernan - Slithy Games
3 REM https://youtu.be/DC5wi6iv9io
4 REM Reference code for speed comparison
10 CLS
20 DIM c(15)
30 FOR n=1 TO 15
40 READ c(n)
50 NEXT n
60 DATA 0,8,16,24,32,40,48,56
70 DATA 72,80,88,96,104,112,120
100 FOR y=0 TO 21
110 FOR x=0 TO 31
120 LET xz=x*3.5/32-2.5
130 LET yz=y*2/22-1
140 LET xx=0
150 LET yy=0
160 FOR i=0 TO 14
170 IF xx*xx+yy*yy>4 THEN GO TO 215
180 LET xt=xx*xx-yy*yy+xz
190 LET yy=2*xx*yy+yz
200 LET xx=xt
210 NEXT i
220 POKE 22528+y*32+x,c(i)
240 NEXT x
250 NEXT y
