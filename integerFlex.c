
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
short toPrec(double f, int bitsPrecision);

int main(int argc, char* argv[])
{
  short log=0;
  short logFrom=27;

  // chosen to match https://www.youtube.com/watch?v=DC5wi6iv9io
  int width = 32; // basic width of a zx81
  int height = 22; // basic width of a zx81
  int zoom=3;  // bigger with finer detail ie a smaller step size - leave at 1 for 32x22

  // params 
  short bitsPrecision = 6;
  printf("PRECISION=%d\n", bitsPrecision);

  short X1 = toPrec(3.5,bitsPrecision) / zoom;
  short X2 = toPrec(2.25,bitsPrecision) ;
  short Y1 = toPrec(3,bitsPrecision)/zoom ;   // horiz pos
  short Y2 = toPrec(1.5,bitsPrecision) ; // vert pos
  short LIMIT = toPrec(4,bitsPrecision);


  // fractal
  //char * chr = ".:-=X$#@.";
  char * chr = "abcdefghijklmnopqr ";
  //char * chr = ".,'~=+:;[/<&?oxOX#.";
  short maxIters = strlen(chr);

  short py=0;
  while (py < height*zoom) {
    short px=0;
    while (px < width*zoom) {

      short x0 = s(s(px*X1) / width) - X2;
      short y0 = s(s(py*Y1) / height) - Y2;

      short x=0;
      short y=0;

      short i=0;

if (0 && log >= logFrom) {
  printf("\n-------\n");
  printf("x0=%4x\n", x0&0xffff);
  printf("y0=%4x\n", y0&0xffff);
}

      short xSqr;
      short ySqr;
      while (i < maxIters) {
        xSqr = s(x * x) >> bitsPrecision;
        ySqr = s(y * y) >> bitsPrecision;

if (0 && log >= logFrom) {
  printf("x =%4x\n", x&0xffff);
  printf("x2=%4x\n", (xSqr)&0xffff);
  printf("y =%4x\n", y&0xffff);
  printf("y2=%4x\n", (ySqr)&0xffff);
  printf("xsq+ysq=%4x\n", (xSqr+ySqr)&0xffff);
  printf("\n");
}

        // Breakout if sum is > the limit OR breakout also if sum is negative which indicates overflow of the addition has occurred
        // The overflow check is only needed for precisions of over 6 bits because for 7 and above the sums come out overflowed and negative therefore we always run to maxIters and we see nothing.
        // By including the overflow break out we can see the fractal again though with noise.
        if ((xSqr + ySqr) >= LIMIT || (xSqr+ySqr) < 0) {
          break;
        }

        short xt = xSqr - ySqr + x0;

if (0 && log >= logFrom) {
  printf("i    =%4x\n", i);
  printf("diff =%4x\n", (xSqr-ySqr)&0xffff);
  printf("xt   =%4x\n", (xt)&0xffff);

  short xy = x*y;
  printf("x*y         =%4x * %4x\n", (x)&0xffff, (y)&0xffff);
  printf("x*y         =%4x\n", (xy)&0xffff);
  printf("x*y>6       =%4x\n", (xy >> 6)&0xffff);
  printf("x*y>6 << 1  =%4x\n", ((short)(xy >> 6) * 2)&0xffff);
  printf("x*y>6<<1+y0 =%4x\n", (((short)((short)(xy >> 6)) << 2)+ y0)&0xffff);
}

        y = s(s(s(x * y) >> bitsPrecision) * 2) + y0;
        x=xt;
        i = i + 1;

      }
if (0 && log >= logFrom) {
  printf("x=%4x  ", x&0xffff);
  printf("xsqr=%4x\n", xSqr&0xffff);
  exit(1);
}


      i = i - 1;


      printf("%c", chr[i]);

      px = px + 1;

      log ++;
    }

    printf("\n");
    py = py + 1;
  }
}

short toPrec(double f, int bitsPrecision) {
// macro to convert a value to a binary string
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x200 ? '1' : '0'), \
  (byte & 0x100 ? '1' : '0'), \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

  short whole = ((short)floor(f) << (bitsPrecision));
  short part = (f-floor(f))*(pow(2,bitsPrecision));
  short ret = whole + part;
  printf(" %3f -> dec: %3d   hex: 0x%04x  bin: %c%c %c%c%c%c%c%c%c%c\n",f, ret, ret, BYTE_TO_BINARY(ret));
  return ret;
}

// convenient casting
short s(short i) {
  return i;
}


