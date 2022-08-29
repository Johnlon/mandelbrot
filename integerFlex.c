
/**
  ascii Mandelbrot using 16 bits of fixed point integer maths with a selectable fractional precision in bits.

  This is still only 16 bits mathc and allocating more than 6 bits of fractional precision leads to an overflow that adds noise to the plot..

  This code frequently casts to short to ensure we're not accidentally benefitting from GCC promotion from short 16 bits to int.

  gcc integerFlex.c  -lm

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

short s(short i);
short toPrec(float f, int bitsPrecision);

// CHOOSE THE NUMBER OF BITS OF PRECISION - 6 is the most I found useful
short bitsPrecision = 6;

int main(int argc, char* argv[])
{
int log=0;

  // chosen to match https://www.youtube.com/watch?v=DC5wi5iv9io
  int width = 32; // basic width of a zx81
  int height = 22; // basic width of a zx81

  printf("PRECISION=%d\n", bitsPrecision);

  short X1 = toPrec(3.5,bitsPrecision);
  short X2 = toPrec(2.5,bitsPrecision) ;
  short Y1 = toPrec(2,bitsPrecision);
  short Y2 = toPrec(1,bitsPrecision) ; // vert pos
  short LIMIT = toPrec(4,bitsPrecision);

  // fractal
  //char * chr = ".:-=X$#@ ";
  //char * chr = "12345678 ";
  char * chr = "123456789ABCDE ";
  //char * chr = ".,'~=+:;[/<&?oxOX#.";
  short maxIters = strlen(chr);

  short py=0;
  while (py < height) {
    short px=0;
    while (px < width) {

      short x0 = s(s(px*X1) / width) - X2;
      short y0 = s(s(py*Y1) / height) - Y2;

      short x=0;
      short y=0;

      short i=0;

      short xSqr;
      short ySqr;
      while (i < maxIters) {
        xSqr = s(x * x) >> bitsPrecision;
        ySqr = s(y * y) >> bitsPrecision;

        // Breakout if sum is > the limit OR breakout also if sum is negative which indicates overflow of the addition has occurred
        // The overflow check is only needed for precisions of over 6 bits because for 7 and above the sums come out overflowed and negative therefore we always run to maxIters and we see nothing.
        // By including the overflow break out we can see the fractal again though with noise.
        short sum =(xSqr + ySqr);
        if (sum > LIMIT) { // || sum < 0) {
          break;
        }

        short xt = xSqr - ySqr + x0;
/*
if (log == 26) {
  printf("\n");
  printf("i    %4x\n", i);
  printf("diff %4x\n", (xSqr - ySqr)&0xffff);
  printf("x %4x\n", x & 0xffff);
  printf("y %4x\n", y & 0xffff);
  printf("m %4x\n", (x*y) & 0xffff);
  printf("m6 %4x\n", (s(x*y)>>6) & 0xffff);
  printf("m1 %4x\n", (s(s(x*y)>>6) <<1) & 0xffff);
}
*/
        y = s(s(s(x * y) >> bitsPrecision) << 1) + y0;
        x=xt;

        i = i + 1;
      }
      i = i - 1;


/*
if (log == 26) {
  exit(1);
}
*/
      //printf("%c", chr[i]);
      //print("\u001b[48;05;${cl}m  \u001b[0m")
      printf("\033[48;05;%dm%02d\033[0m", i, i);

log++;
      px = px + 1;
    }

    printf("\n");
    py = py + 1;
  }
}

// convert decimal value to a fixed point value in the given precision
short toPrec(float f, int bitsPrecision) {
  short whole = ((short)floor(f) << (bitsPrecision));
  short part = (f-floor(f))*(pow(2,bitsPrecision));
  short ret = whole + part;
  printf("%x\n", ret);
  return ret;
}

// convenient casting
short s(short i) {
  return i;
}


