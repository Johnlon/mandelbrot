/*
   SPAM-1 8 Bit ALU experiment.

   16 bit multiply using a pure 8 bit ALU.

   Arithmetic is by 8.8 signed fixed point ops.

 */
#include "stdio.h"
#include "stdlib.h"

// These are the maths ops supported by the SPAM-1 ALU
// Multiply two 8–bit numbers `m` and `n` (unsigned char).
// and return a 8–bit number (unsigned char) representing the hi byte of the result
unsigned char aluMultiply8bitH(unsigned char m, unsigned char n) {
  return ((m*n) >> 8) & 0xff;
}

// Multiply two 8–bit numbers `m` and `n` (unsigned char)
// and return a 8–bit number (unsigned char) representing the hi byte of the result
unsigned char aluMultiply8bitL(unsigned char m, unsigned char n) {
  return (m*n) & 0xff;
}

// Multiply 16–bit integers using SPAM-1 8–bit ALU primitives
unsigned short multiply16bit8p8(unsigned short m, unsigned short n)
{
  // flip both values to positive but remember sign of result
  printf("===\nin m=%x n=%x\n", m,n);
  int sign = 1;
  if (m & 0x8000) {
    sign *= -1;
    m = (m ^ 0xffff) + 1; // supported by SPAM-1
  }
  if (n & 0x8000) {
    sign *= -1;
    n = (n ^ 0xffff) + 1; // supported by SPAM-1
  }
  printf("tx m=%x n=%x  sign=%d\n", m,n, sign);

  // supported by SPAM-1
  unsigned char mLow = (m & 0x00FF);      
  unsigned char mHigh = (m & 0xFF00) >> 8;

  unsigned char nLow = (n & 0x00FF);     
  unsigned char nHigh = (n & 0xFF00) >> 8;

  unsigned char l_mLow_nLow = aluMultiply8bitL(mLow, nLow); 
  unsigned char l_mHigh_nLow = aluMultiply8bitL(mHigh, nLow); 
  unsigned char l_mLow_nHigh = aluMultiply8bitL(mLow, nHigh); 
  unsigned char l_mHigh_nHigh = aluMultiply8bitL(mHigh, nHigh);

  unsigned char h_mLow_nLow = aluMultiply8bitH(mLow, nLow); 
  unsigned char h_mHigh_nLow = aluMultiply8bitH(mHigh, nLow);
  unsigned char h_mLow_nHigh = aluMultiply8bitH(mLow, nHigh);
  unsigned char h_mHigh_nHigh = aluMultiply8bitH(mHigh, nHigh);

  //unsigned short sum = 
  unsigned int sum = 
    //l_mLow_nLow +  // ignore out of range of 8.8 resuly
    ((l_mHigh_nLow + l_mLow_nHigh + h_mLow_nLow) ) + 
    ((h_mHigh_nLow + h_mLow_nHigh + l_mHigh_nHigh) << 8);
//    (h_mHigh_nHigh << 16); // ignore out of range of 8.8 resuly


  // if sign of the result is neg then flip resilt to negative
  if (sign==-1) {
    sum = (sum ^0xffff)+1;
  }

  printf("sum=%x\n", sum);

  return sum;
}

unsigned short s(unsigned short x) {
  return x;
}

int main()
{
  // alu works even with signed values cast to unsigned
  short x = multiply16bit8p8(0x0200,0x0200);
  if (x != 0x0400) { 
    printf("0200 error %x\n", x);
  }

  x = multiply16bit8p8(0x0280,0x0300);
  if (x != 0x0780) { 
    printf("0280 error %x\n", x);
  }

  x = multiply16bit8p8(0xfe00,0xfe00);
  if (x != 0x0400) { 
    printf("fe00 error %x\n", x);
  }

  x = multiply16bit8p8(0xfe00,0x0200);
  if (s(x) != 0xfc00) { 
    printf("fe00,0200 error %x\n", 0xffff&x);
  }

  // test using squares between min short and max short
  for (int j = -32768; j < 32768; j++) {

    unsigned short expected = (j*j) >> 8;

    unsigned short i = j & 0xffff; // truncate and stuff into a short
    unsigned short actual = multiply16bit8p8(i,i) & 0xffff;

    if (expected != actual) {
      printf("expected %x != %x actual\n", expected, actual);
      exit(1);
    }
  }


  return 0;
}
