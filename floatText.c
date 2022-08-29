/**
  ascii Mandelbrot using fixed point integer maths with am "8.8" encoding.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[])
{
  // chosen to match https://www.youtube.com/watch?v=DC5wi6iv9io
  int width = 32; // basic width of a zx81
  int height = 22; // basic width of a zx81
  int zoom=1;  // bigger = finer detail - leave at 1 for 32x22

  // header
  printf("%2s : ", "");
  int w = 0;
  while (w <= width*zoom) {
    if (w%10==0) {
      printf("%-2d", w);
      w ++;
    }
    else printf(" ");
    w ++;
  }
  printf("\n");

  // fractal
  char * chr = ".,'~=+:;[/<&?oxOX# ";
  int iters = strlen(chr);

  int py=0;
  while (py < height*zoom ) {
    printf("%02d : ", py);
    int px=0;
    while (px < width*zoom) {

      double x0 = (((px*3.5)/zoom) / 32) - 2.5;
      double y0 = (((py*2.0)/zoom) / 22) - 1;

      double x=0;
      double y=0;

      int i=0;

      while (i < iters) {
        double xSqr = x * x;
        double ySqr = y * y;

        if ((xSqr + ySqr) > 4) {
          break;
        }

        double xt = xSqr - ySqr + x0;
        y = ((x * y) * 2 ) + y0;
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
