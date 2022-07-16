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

short multiply(short a, short b) {
    // disassemble the args into bytes
    BYTE aHi = (a & 0xff00) >> 8;
    BYTE aLo = a & 0xff;

    BYTE bHi = (b & 0xff00) >> 8;
    BYTE bLo = b & 0xff;

    // perform 8 bit multiplies
    BYTE LLl = timesLo(aLo , bLo);
    BYTE LLh = timesHi(aLo , bLo);

    BYTE LHl = timesLo(aLo , bHi);
    BYTE LHh = timesHi(aLo , bHi);

    BYTE HLl = timesLo(aHi , bLo);
    BYTE HLh = timesHi(aHi , bLo);

    BYTE HHl = timesLo(aHi , bHi);
    BYTE HHh = timesHi(aHi , bHi);


    // sum the parts and carries

    BYTE b0 = LLl;

    BYTE b1CarryA = LLh + LHl > 255? 1:0; // ONLY THE B1 CARRY DOES ANYTHING IN 16 BITS 
    BYTE b1 = LLh + LHl;

    BYTE b1CarryB = b1 + HLl > 255? 1:0; // ONLY THE B1 CARRY DOES ANYTHING IN 16 BITS 
    b1 += HLl;

    //BYTE b2CarryA = LHh + HLh > 255? 1:0;    // NOT NEEDED IN 8.8 SQR unless interested in detecting overflow
    BYTE b2 = LHh + HLh;

    //BYTE b2CarryB = b2 + HHl > 255? 1:0; unless interested in detecting overflow
    b2 += HHl;

    //BYTE b2CarryC = b2 + b1CarryA + b1CarryB > 255? 1:0; unless interested in detecting overflow
    b2 += (b1CarryA + b1CarryB);

    //BYTE b3CarryA = HHh + b2CarryA + b2CarryB + b2CarryC > 255? 1:0; unless interested in detecting overflow
    //BYTE b3 = HHh;

    //BYTE b4 = b3CarryA;

    short sqr = (b2 << 8) + b1;

    return sqr;

}
