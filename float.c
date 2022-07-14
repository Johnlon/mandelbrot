// Floating point implementation

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

char chr [ ]= { '0','1', '2','3','4','5','6','7','8','9','A','B','C','D','E'};

int main(int argc, char* argv[])
{

  printf("%2s : ", "");
  int w = 0;
  while (w <= 51) {
    if (w%10==0) printf("|"); else printf(" ");
    w ++;
  }
  printf("\n");



  int py=0;
  while (py <= 22) {
    printf("%02d : ", py);
    int px=0;
    while (px <= 32) {

      double x0 = ((px*3.5) / 32) - 2.5;
      double y0 = ((py*2.0) / 22) - 1;

      double x=0;
      double y=0;

      int i=0;


      while (i <= 14) {
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

      printf("%1x", i);

      px = px + 1;

    }

    printf("\n");
    py = py + 1;
  }
}
