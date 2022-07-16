/**
  ascii Mandelbrot using fixed point integer maths with an "8.8" encoding.

  shorts (16 bit) chosen for compatibility with a later reimplementation as two bytes per number in assembler.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

void prt(short c, short s) {
   printf("s=%d/%04x     ", s, (0xffff & s));
   printf("c=%d dec/%02d trunc dec / %02x\n", c, 0xff & c, 0xff & c);
}

int main(int argc, char* argv[])
{
  // chosen to match https://www.youtube.com/watch?v=DC5wi6iv9io
  short width = 32; // basic width of a zx81
  short height = 22; // basic width of a zx81
  short zoom=1;  // bigger = finer detail - leave at 1 for 32x22

  // fractal
  char * chr = ".=X ";
  short iters = strlen(chr);

  short py=0;
  while (py < height*zoom) {
    short px=0;
    while (px < width*zoom) {
      // $380 = 3.5      $240=2.25    $180=1.5     $300=3
      short x0 = (((short)(px*0x380)/zoom) >> 5) - 0x240;
      short y0 = ((py*0x300/zoom) >> 4) - 0x180;

      short x=0;
      short y=0;

      short i=0;


      short xSqr;
      short ySqr;
      while (i < iters) {
        xSqr = (x * x) >> 8;
        ySqr = (y * y) >> 8;

        if (i == 1 && px == 1 && py == 0) 
            prt(x, xSqr);

        if ((xSqr + ySqr) > 0x400) {
          break;
        }

        short xt = xSqr - ySqr + x0;
        y = (((x * y)>>8) * 2 ) + y0;
        x=xt;

        i = i + 1;


      }


      i = i - 1;

      printf("%c", chr[i]);

      px = px + 1;

    }

    printf("\n");
    py = py + 1;
  }
}
