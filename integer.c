
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
    if (w%10==0) {
      printf("%-2d", w);
      w ++;
    }
      else printf(" ");
    w ++;
  }
  printf("\n");


  int granularity=1;  // bigger = finer

  int py=0;
  while (py <= 22*granularity) {
    printf("%02d : ", py);
    int px=0;
    while (px <= 32*granularity) {

      short x0 = ((px*0x350/granularity) / 32) - 0x280;
      short y0 = ((py*0x200/granularity) / 22) - 0x100;

      short x=0;
      short y=0;

      int i=0;


      while (i <= 14) {
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


     // if (i ==0) printf(" ");
     // else 
      printf("%1x", i);

      px = px + 1;

    }

    printf("\n");
    py = py + 1;
  }
}