/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

int test_absVal(int x) {
  return (x < 0) ? -x : x;
}
int test_addOK(int x, int y)
{
    long long lsum = (long long) x + y;
    return lsum == (int) lsum;
}
int test_allEvenBits(int x) {
  int i;
  for (i = 0; i < 32; i+=2)
      if ((x & (1<<i)) == 0)
   return 0;
  return 1;
}
//#include "allOddBits.c"
//#include "anyEvenBit.c"
//#include "anyOddBit.c"
int test_bang(int x)
{
  return !x;
}
//#include "bitAnd.c"
int test_bitCount(int x) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result += (x >> i) & 0x1;
  return result;
}
//#include "bitMask.c"
int test_bitNor(int x, int y)
{
  return ~(x|y);
}
//#include "bitOr.c"
//#include "bitParity.c"
//#include "bitXor.c"

int test_byteSwap(int x, int n, int m)
{
    /* little endiamachine */
    /* least significant byte stored first */

    unsigned int nmask, mmask;

    switch(n) {
    case 0:
      nmask = x & 0xFF;
      x &= 0xFFFFFF00;
      break;
    case 1:
      nmask = (x & 0xFF00) >> 8;
      x &= 0xFFFF00FF;
      break;
    case 2:
      nmask = (x & 0xFF0000) >> 16;
      x &= 0xFF00FFFF;
      break;
    default:
      nmask = ((unsigned int)(x & 0xFF000000)) >> 24;
      x &= 0x00FFFFFF;
      break;
    }

    switch(m) {
    case 0:
      mmask = x & 0xFF;
      x &= 0xFFFFFF00;
      break;
    case 1:
      mmask = (x & 0xFF00) >> 8;
      x &= 0xFFFF00FF;
      break;
    case 2:
      mmask = (x & 0xFF0000) >> 16;
      x &= 0xFF00FFFF;
      break;
    default:
      mmask = ((unsigned int)(x & 0xFF000000)) >> 24;
      x &= 0x00FFFFFF;
      break;
    }

    nmask <<= 8*m;
    mmask <<= 8*n;

    return x | nmask | mmask;
}
int test_conditional(int x, int y, int z)
{
  return x?y:z;
}
//#include "copyLSB.c"
//#include "divpwr2.c"
//#include "evenBits.c"
int test_ezThreeFourths(int x)
{
  return (x*3)/4;
}
int test_fitsBits(int x, int n)
{
  int TMin_n = -(1 << (n-1));
  int TMax_n = (1 << (n-1)) - 1;
  return x >= TMin_n && x <= TMax_n;
}
//#include "fitsShort.c"
//#include "float_abs.c"
//#include "float_f2i.c"
//#include "float_half.c"
//#include "float_i2f.c"
//#include "float_neg.c"
//#include "float_twice.c"
int test_getByte(int x, int n)
{
    unsigned char byte;
    switch(n) {
    case 0:
      byte = x;
      break;
    case 1:
      byte = x >> 8;
      break;
    case 2:
      byte = x >> 16;
      break;
    default:
      byte = x >> 24;
      break;
    }
    return (int) (unsigned) byte;
}
int test_greatestBitPos(int x) {
    unsigned mask = 1<<31;
    if (x == 0)
 return 0;
    while (!(mask & x)) {
 mask = mask >> 1;
    }
    return mask;
}
//#include "howManyBits.c"
//#include "ilog2.c"
int test_implication(int x, int y)
{
  return !(x & (!y));
}
int test_isAsciiDigit(int x) {
  return (0x30 <= x) && (x <= 0x39);
}
int test_isEqual(int x, int y)
{
  return x == y;
}
//#include "isGreater.c"
int test_isLess(int x, int y)
{
  return x < y;
}
//#include "isLessOrEqual.c"
//#include "isNegative.c"
int test_isNonNegative(int x) {
  return x >= 0;
}
//#include "isNonZero.c"
//#include "isNotEqual.c"
//#include "isPositive.c"
int test_isPower2(int x) {
  int i;
  for (i = 0; i < 31; i++) {
    if (x == 1<<i)
      return 1;
  }
  return 0;
}
//#include "isTmax.c"
int test_isTmin(int x) {
    return x == 0x80000000;
}
//#include "isZero.c"
//#include "leastBitPos.c"
//#include "leftBitCount.c"
//#include "logicalNeg.c"
//#include "logicalShift.c"
int test_minusOne(void) {
  return -1;
}
//#include "multFiveEighths.c"
//#include "negate.c"
//#include "oddBits.c"
//#include "rempwr2.c"
//#include "replaceByte.c"
//#include "reverseBytes.c"
int test_rotateLeft(int x, int n) {
  unsigned u = (unsigned) x;
  int i;
  for (i = 0; i < n; i++) {
      unsigned msb = u >> 31;
      unsigned rest = u << 1;
      u = rest | msb;
  }
  return (int) u;
}
//#include "rotateRight.c"
//#include "satAdd.c"
int test_satMul2(int x)
{
  if ((x+x)/2 != x)
    return x < 0 ? 0x80000000 : 0x7FFFFFFF;
  else
    return 2*x;
}
//#include "satMul3.c"
//#include "sign.c"
//#include "sm2tc.c"
//#include "subOK.c"
//#include "tc2sm.c"
//#include "thirdBits.c"
//#include "tmax.c"
//#include "tmin.c"
//#include "trueFiveEighths.c"
//#include "trueThreeFourths.c"
//#include "upperBits.c"
