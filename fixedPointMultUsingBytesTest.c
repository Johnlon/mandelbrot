/*
   fixed point 8.8 multiply demonstrated using unsigned char for the upper and lower bytes.
   care has been taken to avoid the affects of the compiler promoting 8 bit values to 16/42 during the maths.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

short multiply(short a, short b);

double convertFixedToFloat(short a) {
  unsigned short iPart = (0xff00 & a) >> 8;
  unsigned short fPart = a & 0xff;
  return iPart + fPart/256.0;
}

/* both args are a fixed point 8.8 number **/
void times(short a, short b) {
  // construct expected result in decimal float
  double aFloatingPoint = convertFixedToFloat(a);
  double bFloatingPoint = convertFixedToFloat(b);

  // calculated expected product using floating point multiply and convert back to 8.8 fixed point
  float expectedF = (aFloatingPoint * bFloatingPoint);
  unsigned short expected88I = expectedF; // truncates
  unsigned short expected88F = 256 * ((expectedF - expected88I));
  unsigned short expectedFixedPoint = expected88I * 256 + expected88F;

  // perform fixed point calc using bytes
  unsigned short actualProduct = multiply(a,b);

  short roundingError = 1;
  short diff = abs(actualProduct - expectedFixedPoint);
  if (diff > roundingError) {
    printf("\n");
    printf(" a=x%04x ", 0xffff&a); 
    printf(" b=x%04x ", 0xffff&b);

    printf(" aFP=%f ", aFloatingPoint);
    printf(" bFP=%f ", bFloatingPoint);

    printf(" expected %d/%04x    got  %d/%04x \n", expectedFixedPoint&0xffff, expectedFixedPoint&0xffff, actualProduct, actualProduct);
    printf("err");
    exit(1);
  }
}

void main() {


  /*
     times(0, 0, 0);
     times(0x0001, 0x0001, 0x0000);
     times(0x0002, 0x0002, 0x0000);
     times(0x000f, 0x000f, 0x0000);
     times(0x0010, 0x0010, 0x0001);
     times(0x0011, 0x0011, 0x0001);
     times(0x0019, 0x0019, 0x0002);
     times(0x0020, 0x0020, 0x0004);
     times(0x0022, 0x0022, 0x0004);
     times(0x0023, 0x0023, 0x0004);
     times(0x0024, 0x0024, 0x0005);
     times(0x0025, 0x0025, 0x0005);
     times(0x0026, 0x0026, 0x0005);
     times(0x0027, 0x0027, 0x0005);
     times(0x0040, 0x0040, 0x0010);
     times(0x0100, 0x0040, 0x0040);
     times(0x0100, 0x0100, 0x0100);
     times(0x0c00, 0x0c00, 0x9000);
     times(0x0c01, 0x0c01, 0x9018);
     times(0x0c0c, 0x0c0c, 0x9120);
     times(0x0f0f, 0x0f0f, 0xe2c2);
     times(0x0f10, 0x0f0f, 0xe2d1);
     times(0x0fff, 0x1001, 0xffff);  // 4095 x 4097 max value


     printf("\nSQUARES \n");

     for (int i=0; i< 0xffff; i++) {
     short ip = (0xff00 & i) >> 8;
     short fp = i & 0xff;

     double n = ip + fp/256.0;

     printf("\n I: x%04x ", i);
     printf(" IPart: x%02x ", ip);
     printf(" FPart: x%02x ", fp);
     printf("\t N: %f ", n);
     printf("\t N2: %f ", n*n);

     times(i, i, 256*(n * n));
     }

   */
  printf("\nALL \n");
  for (int i=1; i<= 0xffff; i++) {
    for (int j=0; j<= 0xffff; j++) {
      times(i, j);
    }
    //printf("%d\n", i);
  }

}


