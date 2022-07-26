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

short num(double f, int dec) {
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

  short whole = ((short)floor(f) << (dec));
  short part = (f-floor(f))*(pow(2,dec));
  short ret = whole + part;
  printf(" %3f -> %3d 0x%04x  %c%c %c%c%c%c%c%c%c%c\n",f, ret, ret, BYTE_TO_BINARY(ret));
  return ret;
}

int main(int argc, char* argv[])
{
  // chosen to match https://www.youtube.com/watch?v=DC5wi6iv9io
  short width = 32; // basic width of a zx81
  short height = 22; // basic width of a zx81
  short zoom=1;  // bigger with finer detail ie a smaller step size - leave at 1 for 32x22

  // params
  short decs = 6;
  printf("DECS=%d\n", decs);
  short X1 = num(3.5,decs) / zoom;
  short X2 = num(2.25,decs) ;

  short Y1 = num(3,decs)/zoom ;   // horiz pos
  short Y2 = num(1.5,decs) ; // vert pos
  short LIMIT = num(4,decs);


  // fractal
  char * chr = ".:-=X$#@ ";
  short iters = strlen(chr);

  short py=0;
  while (py < height*zoom) {
    short px=0;
    while (px < width*zoom) {

      //short x0 = (((short)(px*X1)/zoom) / width) - X2;
      //short y0 = (((short)(py*Y1)/zoom) / height) - Y2;
      short x0 = (((short)(px*X1)) / width) - X2;
      short y0 = (((short)(py*Y1)) / height) - Y2;

      short x=0;
      short y=0;

      short i=0;


      short xSqr;
      short ySqr;
      while (i < iters) {
        xSqr = (short)(x * x) >> decs;
        ySqr = (short)(y * y) >> decs;

        // breakout also if negative as this indicates overflow of the addition which is a fault
        if ((xSqr + ySqr) > LIMIT || (xSqr+ySqr) < 0) {
          break;
        }

        short xt = xSqr - ySqr + x0;
        y = (((x * y)>>decs) * 2 ) + y0;
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
