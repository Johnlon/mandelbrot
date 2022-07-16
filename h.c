#include <stdio.h>

void main() {

/*
  short x = 0xc0;

  short x1 = (x * x);
  short xs = x1 >> 8;

  printf("%d %d  %x \n", xs, 0xffff & xs, 0xffff & xs);

  short y1 = (x * x) >> 8;
  printf("%d %d  %x \n", y1, 0xffff & y1, 0xffff & y1);

  unsigned char xlo = x & 0xff;
  unsigned char xhi = (x & 0xff00)>>8;
*/

  unsigned char ___X(short n) {
    return n & 0xf;
  }
  unsigned char __X_(short n) {
    return (n & 0xf0) >> 4;
  }

  unsigned char _X__(short n) {
    return (n & 0xf00) >> 8;
  }
  unsigned char X___(short n) {
    return (n & 0xf000) >> 12;
  }

  unsigned char uc(unsigned n) {
    return n;
  }

  short fixedPtMultiply2(short a, short b) {
    return (0
      + (uc((___X(a) * ___X(b))) << 0)
      + (uc((___X(a) * __X_(b))) << 4)
      + (uc((___X(a) * _X__(b))) << 8)
      + (uc((___X(a) * X___(b))) << 12)

      + (uc((__X_(a) * ___X(b))) << 4)
      + (uc((__X_(a) * __X_(b))) << 8)
      + (uc((__X_(a) * _X__(b))) << 12)
      + (uc((__X_(a) * X___(b))) << 16)

      + (uc((_X__(a) * ___X(b))) << 8)
      + (uc((_X__(a) * __X_(b))) << 12)
      + (uc((_X__(a) * _X__(b))) << 16)
      + (uc((_X__(a) * X___(b))) << 20)

      + (uc((X___(a) * ___X(b))) << 12)
      + (uc((X___(a) * __X_(b))) << 16) 
      + (uc((X___(a) * _X__(b))) << 20)
      + (uc((X___(a) * X___(b))) << 24)
      ) >> 8
      ;
  }



  short fixedPtMultiply1(short a, short b) {
    return (0
      + (short)(uc((___X(a) * ___X(b))) << 0)
      + (short)(uc((___X(a) * __X_(b))) << 4)
      + (short)(uc((___X(a) * _X__(b))) << 8)
      + (short)(uc((___X(a) * X___(b))) << 12)

      + (short)(uc((__X_(a) * ___X(b))) << 4)
      + (short)(uc((__X_(a) * __X_(b))) << 8)
      + (short)(uc((__X_(a) * _X__(b))) << 12)
      + (short)(uc((__X_(a) * X___(b))) << 16)

      + (short)(uc((_X__(a) * ___X(b))) << 8)
      + (short)(uc((_X__(a) * __X_(b))) << 12)
      + (short)(uc((_X__(a) * _X__(b))) << 16)
      + (short)(uc((_X__(a) * X___(b))) << 20)

      + (short)(uc((X___(a) * ___X(b))) << 12)
      + (short)(uc((X___(a) * __X_(b))) << 16) 
      + (short)(uc((X___(a) * _X__(b))) << 20)
      + (short)(uc((X___(a) * X___(b))) << 24)
      ) >> 8
      ;
  }

  short fixedPtMultiply3(short a, short b) {
    return (0
      + (short)(uc((___X(a) * ___X(b))) << 0)
      + (short)(uc((___X(a) * __X_(b))) << 4)
      + (short)(uc((___X(a) * _X__(b))) << 8)
      + (short)(uc((___X(a) * X___(b))) << 12)

      + (short)(uc((__X_(a) * ___X(b))) << 4)
      + (short)(uc((__X_(a) * __X_(b))) << 8)
      + (short)(uc((__X_(a) * _X__(b))) << 12)
      + (short)(uc((__X_(a) * X___(b))) << 16)

      + (short)(uc((_X__(a) * ___X(b))) << 8)
      + (short)(uc((_X__(a) * __X_(b))) << 12)
      + (short)(uc((_X__(a) * _X__(b))) << 16)
      + (short)(uc((_X__(a) * X___(b))) << 20)

      + (short)(uc((X___(a) * ___X(b))) << 12)
      + (short)(uc((X___(a) * __X_(b))) << 16) 
      + (short)(uc((X___(a) * _X__(b))) << 20)
      + (short)(uc((X___(a) * X___(b))) << 24)
      ) >> 8
      ;
  }

  unsigned char lo(short a, short b) {
    return (0
      + (unsigned char)(uc((___X(a) * ___X(b))) << 0)
      + (unsigned char)(uc((___X(a) * __X_(b))) << 4)
      + (unsigned char)(uc((___X(a) * _X__(b))) << 8)
      + (unsigned char)(uc((___X(a) * X___(b))) << 12)

  //    + (unsigned char)(uc((__X_(a) * ___X(b))) << 4)
      + (unsigned char)(uc((__X_(a) * __X_(b))) << 8)
      + (unsigned char)(uc((__X_(a) * _X__(b))) << 12)
   //   + (unsigned char)(uc((__X_(a) * X___(b))) << 16)

  //    + (unsigned char)(uc((_X__(a) * ___X(b))) << 8)
  //    + (unsigned char)(uc((_X__(a) * __X_(b))) << 12)
  //    + (unsigned char)(uc((_X__(a) * _X__(b))) << 16)
  //    + (unsigned char)(uc((_X__(a) * X___(b))) << 20)

   //   + (unsigned char)(uc((X___(a) * ___X(b))) << 12)
   //   + (unsigned char)(uc((X___(a) * __X_(b))) << 16) 
   //   + (unsigned char)(uc((X___(a) * _X__(b))) << 20)
    //  + (unsigned char)(uc((X___(a) * X___(b))) << 24)
      ) 
//>> 8
      ;
  }
  unsigned char hi(short a, short b) {
    return (0
//      + (unsigned char)(uc((___X(a) * ___X(b))) << 0)
//      + (unsigned char)(uc((___X(a) * __X_(b))) << 4)
//      + (unsigned char)(uc((___X(a) * _X__(b))) << 8)
//      + (unsigned char)(uc((___X(a) * X___(b))) << 12)

//      + (unsigned char)(uc((__X_(a) * ___X(b))) << 4)
//      + (unsigned char)(uc((__X_(a) * __X_(b))) << 8)
//      + (unsigned char)(uc((__X_(a) * _X__(b))) << 12)
      + (unsigned char)(uc((__X_(a) * X___(b))) << 16)

//      + (unsigned char)(uc((_X__(a) * ___X(b))) << 8)
//      + (unsigned char)(uc((_X__(a) * __X_(b))) << 12)
      + (unsigned char)(uc((_X__(a) * _X__(b))) << 16)
      + (unsigned char)(uc((_X__(a) * X___(b))) << 20)

//      + (unsigned char)(uc((X___(a) * ___X(b))) << 12)
      + (unsigned char)(uc((X___(a) * __X_(b))) << 16) 
      + (unsigned char)(uc((X___(a) * _X__(b))) << 20)
//      + (unsigned char)(uc((X___(a) * X___(b))) << 24)
      ) 
//>> 8
      ;
  }

  short two(short a, short b) {
    return lo(a,b) +  hi(a,b) << 8;
  }

  void test(short a, short b, short expected) {
    //short sqr = fixedPtMultiply1(a, b);
    short sqr = two(a, b);
    if (sqr != expected) {
      printf("a=%-5d/%4x b=%-5d and expected %-5d %04x but got   %-5d(dec) %-5d(dec trunc)  %x \n", a, a,b,expected, expected, sqr, 0xffff & sqr, 0xffff & sqr);
    }
  }

  test(0,0,0);
  test(0x0001,0x0001,0x0000);
  test(0x0002,0x0002,0x0000);
  test(0x0040,0x0040,0x0010); // .25*.25=.00625
  test(0x0100,0x0040,0x0040); 
  test(0x0100,0x0100,0x0100);
  test(0x0c00,0x0c00,0x9000);


}

