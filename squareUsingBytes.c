/*
  fixed point 8.8 multiply demonstrated using unsigned char for the upper and lower bytes.
  care has been taken to avoid the affects of the compiler promoting 8 bit values to 16/32 during the maths.
*/
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

// SPAM-1 CPU ALU operation supports this
BYTE timesLo(BYTE a, BYTE b) {
    return  ((a * b) & 0xff);
}

// SPAM-1 CPU ALU operation supports this
BYTE timesHi(BYTE a, BYTE b) {
    return  ((a * b) & 0xff00) >> 8;
}



void testSqD(short a, short b, short expected, short d) {
    // disassemble the args into bytes
    BYTE aHi = (a & 0xff00) >> 8;
    BYTE aLo = a & 0xff;

    BYTE bHi = (b & 0xff00) >> 8;
    BYTE bLo = b & 0xff;
/*
    printf("----------------\n");
    printf("aHi   %5d  %02x \n", aHi , aHi);
    printf("aLo   %5d  %02x \n", aLo , aLo);

    printf("bHi   %5d  %02x \n", bHi , bHi);
    printf("bLo   %5d  %02x \n", bLo , bLo);
    */

    BYTE LLl = timesLo(aLo , bLo);
    BYTE LLh = timesHi(aLo , bLo);

    BYTE LHl = timesLo(aLo , bHi);
    BYTE LHh = timesHi(aLo , bHi);

    BYTE HLl = timesLo(aHi , bLo);
    BYTE HLh = timesHi(aHi , bLo);

    BYTE HHl = timesLo(aHi , bHi);
    BYTE HHh = timesHi(aHi , bHi);

    /*
    puts("");
    printf("LLl   %5d  %02x \n", LLl , LLl);
    printf("LLh   %5d  %02x \n", LLh , LLh);
    printf("LHl   %5d  %02x \n", LHl , LHl);
    printf("LHh   %5d  %02x \n", LHh , LHh);
    printf("HLl   %5d  %02x \n", HLl , HLl);
    printf("HLh   %5d  %02x \n", HLh , HLh);
    printf("HHl   %5d  %02x \n", HHl , HHl);
    printf("HHh   %5d  %02x \n", HHh , HHh);
    puts("");
     */

    BYTE b0 = LLl;

    BYTE b1CarryA = LLh + LHl > 255? 1:0;
    BYTE b1 = LLh + LHl;

    BYTE b1CarryB = b1 + HLl > 255? 1:0;
    b1 += HLl;

    BYTE b2CarryA = LHh + HLh > 255? 1:0;
    BYTE b2 = LHh + HLh;

    BYTE b2CarryB = b2 + HHl > 255? 1:0;
    b2 += HHl;

    BYTE b2CarryC = b2 + b1CarryA + b1CarryB > 255? 1:0;
    b2 += (b1CarryA + b1CarryB);

    BYTE b3CarryA = HHh + b2CarryA + b2CarryB + b2CarryC > 255? 1:0;
    BYTE b3 = HHh;

    BYTE b4 = b3CarryA;

    /*
    printf("b0   %5d  %02x \n", b0 , b0);
    printf("b1   %5d  %02x     c %d %d\n", b1 , b1,  b1CarryA, b1cb);
    printf("b2   %5d  %02x     c %d %d %d\n", b2 , b2, b2CarryA, b2CarryB, b2cc);
    printf("b3   %5d  %02x     c %d\n", b3 , b3, CarryB3a);
    printf("b4   %5d  %02x \n", b4 , b4);
     */

    //short sqr = b1 + (b2 << 8);
    short sqr = (b2 << 8) + b1;

    //short sqr = fixedPtMultiply1(a, b);
    //    short sqr = two(a, b);
    printf("\ta=%d/%04x \tb=%d/%04x  \texpected %d/%04x  \tgot  %d/%04x \n", a, 0xffff&a, b,0xffff&b,expected&0xffff, expected&0xffff, sqr, sqr);
    if (  ( d != 0 && (sqr < expected-d || sqr > expected+d)) || (d ==0 && sqr != expected)) {
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

    printf("MANUAL PASS \n");

    for (int i=0; i< 0xffff; i++) {
        short ip = (0xff00 & i) >> 8;
        short fp = i & 0xff;

        double n = ip + fp/256.0;

        printf(" I: x%04x ", i);
        printf(" IPart: x%02x ", ip);
        printf(" FPart: x%02x ", fp);
        printf("\t N: %f ", n);
        printf("\t N2: %f ", n*n);

        testSqD(i, i, 256*(n * n), 10);
    }

}


