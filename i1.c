
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
  int log=0;

  printf("%2s : ", "");
  int w = 0;
  while (w <= 51) {
    if (w%10==0) printf("|"); else printf(" ");
    w ++;
  }
  printf("\n");

  //char * chr = ".,'~=+:;[/<&?oxOX# ";
  char * chr = "0123C4567890ABCDEF";


  //  char * chr = ".,'~=+:;[/<&?oxOX# ";
  int iters=  strlen(chr);
  printf("iters = %5d\n", iters);

  // https://rosettacode.org/wiki/Mandelbrot_set#BASIC
  short xmin = -2.0 * 256 ;
  short xmax = 1 * 256; 
  short ymin = -1.5 * 256;
  short ymax = 1.5 * 256;

  short W = 64;
  short H = 48;
  short step = 1; //  use e.g. st = .05 for a coarser but faster picture and perhaps also lower maxIteration = 10 or so
  short dx = ((xmax-xmin) / W);
  short dy = ((ymax-ymin) / H);

  printf("DX=%d ", dx);
  printf("DY=%d\n", dy);

  for (int y0 = 0; y0< H; y0+=1) {

    for (int x0 = 0; x0< W; x0+=1) {
      short  x = 0;
      short  y = 0;
      short  i = 0;

      if (log) printf("==============================\n");

      for (; i < iters && ( ((x*x)>>8) + ((y*y)>>8) <= 0x400); i++) {

        short xtemp = ((x*x)>>8) - ((y*y)>>8) + ((x0*dx) >> 8);

        if (log) printf("x0 = %4x  ", x0);
        if (log) printf("y0 = %4x  ", y0);
        if (log) printf("xa = %4x ^ %4x    ", x, (x*x)>>8);
        if (log) printf("ya = %4x ^ %4x    ", y, (y*y)>>8);
        if (log) printf("t = %4x       ", xtemp);

        y = 2 * ((x * y)>>8 ) + ((y0*dy) >> 8);
        x = xtemp;

        //      printf("xb = %4x ^ %4x    ", x, (x*x) >>  8);
        //     printf("yb = %4x ^ %4x    \n", y, (y*y) >> 8);
      }

      //    printf("\nBREAK i=%4x   x2+y2=%x \n ", i, (x*(x>>8)) + (y*(y>>8)));
      if (i < iters) {
        printf("%c", chr[i]);
      } 
      else {
        printf("!");
      } 

    }
    printf("\n");
  }
}
