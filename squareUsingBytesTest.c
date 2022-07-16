/*
  fixed point 8.8 multiply demonstrated using unsigned char for the upper and lower bytes.
  care has been taken to avoid the affects of the compiler promoting 8 bit values to 16/32 during the maths.
*/
#include <stdio.h>
#include <stdlib.h>

short square(short a, short b);

void testSqD(short a, short b, short expected, short d) {

    short sqr = square(a,b);

    if (  (d ==0 && sqr != expected)) {
        printf("\ta=%d/%04x \tb=%d/%04x  \texpected %d/%04x  \tgot  %d/%04x \n", a, 0xffff&a, b,0xffff&b,expected&0xffff, expected&0xffff, sqr, sqr);
        printf("err");
        exit(1);
    }

}
void testSq(short a, short b, short expected) {
   testSqD(a, b, expected, 0);
}

void main() {


    testSq(0, 0, 0);
    testSq(0x0001, 0x0001, 0x0000);
    testSq(0x0002, 0x0002, 0x0000);
    testSq(0x000f, 0x000f, 0x0000);
    testSq(0x0010, 0x0010, 0x0001);
    testSq(0x0011, 0x0011, 0x0001);
    testSq(0x0019, 0x0019, 0x0002);
    testSq(0x0020, 0x0020, 0x0004);
    testSq(0x0022, 0x0022, 0x0004);
    testSq(0x0023, 0x0023, 0x0004);
    testSq(0x0024, 0x0024, 0x0005);
    testSq(0x0025, 0x0025, 0x0005);
    testSq(0x0026, 0x0026, 0x0005);
    testSq(0x0027, 0x0027, 0x0005);
    testSq(0x0040, 0x0040, 0x0010);
    testSq(0x0100, 0x0040, 0x0040);
    testSq(0x0100, 0x0100, 0x0100);
    testSq(0x0c00, 0x0c00, 0x9000);
    testSq(0x0c01, 0x0c01, 0x9018);
    testSq(0x0c0c, 0x0c0c, 0x9120);
    testSq(0x0f0f, 0x0f0f, 0xe2c2);
    testSq(0x0f10, 0x0f0f, 0xe2d1);
    testSq(0x0fff, 0x1001, 0xffff);  // 4095 x 4097 max value


    printf("SQUARES \n");

    for (int i=0; i< 0xffff; i++) {
        short ip = (0xff00 & i) >> 8;
        short fp = i & 0xff;

        double n = ip + fp/256.0;

        printf("\n I: x%04x ", i);
        printf(" IPart: x%02x ", ip);
        printf(" FPart: x%02x ", fp);
        printf("\t N: %f ", n);
        printf("\t N2: %f ", n*n);

        testSqD(i, i, 256*(n * n), 1);
    }

    printf("ALL \n");
    for (int i=0; i< 0xffff; i++) {
      for (int j=0; j< 0xffff; j++) {
        short ipI = (0xff00 & i) >> 8;
        short fpI = i & 0xff;
        double nI = ipI + fpI/256.0;

        short ipJ = (0xff00 & i) >> 8;
        short fpJ = i & 0xff;
        double nJ = ipJ + fpJ/256.0;

        // printf("I: x%04x ", i); 
        // printf("J: x%04x ", j);

        //printf(" IPart: x%02x ", ip);
        //printf(" FPart: x%02x ", fp);
        //printf("\t N: %f ", n);
        //printf("\t N2: %f ", n*n);

        testSqD(i, j, 256*(nI * nJ), 1);
      }
    }

}


