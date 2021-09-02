#include <stdio.h>
static unsigned char color[] = {
		0,0,17,19,
		21,33,45,51,49,47,82,154,226,220,208,196
	};

int mandi(x,y)
int x,y;
{
	float xz,yz,xx,yy,xt;
	int i;
	
	xz = x*3.5/32.0-2.5;
	yz = y*2.0/22.0-1.0;
	xx = 0;
	yy = 0;

	for (i=0;i<15;i++) {
		if (xx*xx + yy*yy > 4.0) return i;
		xt = xx*xx - yy*yy + xz;
		yy = 2.0*xx*yy + yz;
		xx = xt;
	}
	
	return i;
}

int main() {
	int x,y;
	for (y=0;y<22;y++) {
		for (x=0;x<32;x++) {
			printf(
				"\033[48;5;%dm  ",
				color[mandi(x,y)]
			);
		}
		printf("\033[m\n");
	}
	return 0;
}
