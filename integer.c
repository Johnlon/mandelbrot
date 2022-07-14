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
  while (py < height*zoom) {
    printf("%02d : ", py);
    int px=0;
    while (px < width*zoom) {
      // $380 = 3.5      $240=2.25    $180=1.5     $300=3
      short x0 = ((px*0x380/zoom) / width) - 0x240;
      short y0 = ((py*0x300/zoom) / height) - 0x180;

      short x=0;
      short y=0;

      int i=0;

      while (i < iters) {
        short xSqr = (x * x) >> 8;
        short ySqr = (y * y) >> 8;

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
