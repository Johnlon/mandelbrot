
/**
  ascii Mandelbrot using 16 bits of fixed pofloat integer maths with a selectable fractional precision in bits.

  This is still only 16 bits mathc and allocating more than 6 bits of fractional precision leads to an overflow that adds noise to the plot..

  This code frequently casts to float to ensure we're not accidentally benefitting from GCC promotion from float 16 bits to int.

  gcc integerFlex.c  -lm

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#define  c_black 	 0
#define  c_white 	 15
#define  c_red 	 1
#define  c_cyan 	 14
#define  c_purple 	 206
#define  c_green 	 10
#define  c_blue 	 4
#define  c_yellow 	 226
#define  c_orange 	 202
#define  c_brown 	 94
#define  c_salmon 	 167
#define  c_grey 	59 
#define  c_l_brown 	 8
#define  c_lime 	 83
#define  c_m_blue 	 38 
 
int colourMap[] = {
  c_black,
  c_white,
  c_red,
  c_cyan,
  c_purple,
  c_green,
  c_blue,
  c_yellow, 
  c_orange,
  c_brown,
  c_salmon, 
  c_grey, 
  c_l_brown, 
  c_lime,
  c_m_blue, 
};


float main(float argc, char* argv[])
{
float log=0;

  // chosen to match https://www.youtube.com/watch?v=DC5wi6iv9io
  float width = 32; // basic width of a zx81
  float height = 22; // basic width of a zx81
  float zoom=1;  // bigger with finer detail ie a smaller step size - leave at 1 for 32x22

  // params 

  float X1 = 3.5;
  float X2 = 2.5;
  float Y1 = 2;
  float Y2 = 1;
  float LIMIT = 4;

  // fractal
  char * chr = "123456789ABCDE ";
  float maxIters = strlen(chr);

  float py=0;
  while (py < height*zoom) {
    float px=0;
    while (px < width*zoom) {

      float x0 = ((px*X1) / width) - X2;
      float y0 = ((py*Y1) / height) - Y2;

      float x=0;
      float y=0;

      int i=0;

      while (i < maxIters) {
        float xSqr = (x * x);
        float ySqr = (y * y);

        // Breakout if sum is > the limit OR breakout also if sum is negative which indicates overflow of the addition has occurred
        // The overflow check is only needed for precisions of over 6 bits because for 7 and above the sums come out overflowed and negative therefore we always run to maxIters and we see nothing.
        // By including the overflow break out we can see the fractal again though with noise.
        float sum =(xSqr + ySqr);
        if (sum > LIMIT) { // || sum < 0) {
          break;
        }

        float xt = xSqr - ySqr + x0;
/*
if (log == 26) {
  printf("\n");
  printf("i    %4x\n", i);
  printf("diff %4x\n", (xSqr - ySqr)&0xffff);
  printf("x %4x\n", x & 0xffff);
  printf("y %4x\n", y & 0xffff);
  printf("m %4x\n", (x*y) & 0xffff);
  printf("m6 %4x\n", ((x*y)>>6) & 0xffff);
  printf("m1 %4x\n", (((x*y)>>6) <<1) & 0xffff);
}
*/
        y = (((x * y)) * 2) + y0;
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
      int c = colourMap[i];
      //printf("\033[48;05;%dm  \033[0m", c, i);
      printf("\033[48;05;%dm%02d\033[0m", c, i);

log++;
      px = px + 1;
    }

    printf("\n");
    py = py + 1;
  }
}



