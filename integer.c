/**
DOESNT WORT WHEN ALL TREMP VALS ARE SHORT

  ascii Mandelbrot using fixed point integer maths with an "8.8" encoding.

  shorts (16 bit) chosen for compatibility with a later reimplementation as two bytes per number in assembler.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

short s(short i) {
  return i;
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
      short x0 = s(s(s(px*0x380)/zoom) / 32) - 0x240;
      short y0 = s(s(s(py*0x300)/zoom) / 22) - 0x180;

      short x=0;
      short y=0;

      short i=0;

      short xSqr;
      short ySqr;
      while (i < iters) {
        xSqr = s(x * x) >> 8;
        ySqr = s(y * y) >> 8;

        if ((xSqr + ySqr) > 0x400) {
          break;
        }

        short xt = xSqr - ySqr + x0;
        y = (s(s(x * y)>>8) * 2 ) + y0;
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
