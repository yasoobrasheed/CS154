#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {





 {"absVal", (funct_t) absVal, (funct_t) test_absVal, 1, "! ~ & ^ | + << >>", 10, 4,
  {{-TMax, TMax},{TMin,TMax},{TMin,TMax}}},
 {"addOK", (funct_t) addOK, (funct_t) test_addOK, 2,
    "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"allEvenBits", (funct_t) allEvenBits, (funct_t) test_allEvenBits, 1,
    "! ~ & ^ | + << >>", 12, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "allOddBits.c"
//#include "anyEvenBit.c"
//#include "anyOddBit.c"
 {"bang", (funct_t) bang, (funct_t) test_bang, 1,
    "~ & ^ | + << >>", 12, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "bitAnd.c"
 {"bitCount", (funct_t) bitCount, (funct_t) test_bitCount, 1, "! ~ & ^ | + << >>", 40, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "bitMask.c"
 {"bitNor", (funct_t) bitNor, (funct_t) test_bitNor, 2, "& ~", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "bitOr.c"
//#include "bitParity.c"
//#include "bitXor.c"
{"byteSwap", (funct_t) byteSwap, (funct_t) test_byteSwap, 3,
     "! ~ & ^ | + << >>", 25, 2,
    {{TMin, TMax},{0,3},{0,3}}},
 {"conditional", (funct_t) conditional, (funct_t) test_conditional, 3, "! ~ & ^ | << >>", 16, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "copyLSB.c"
//#include "divpwr2.c"
//#include "evenBits.c"
 {"ezThreeFourths", (funct_t) ezThreeFourths, (funct_t) test_ezThreeFourths, 1,
    "! ~ & ^ | + << >>", 12, 3,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"fitsBits", (funct_t) fitsBits, (funct_t) test_fitsBits, 2,
    "! ~ & ^ | + << >>", 15, 2,
  {{TMin, TMax},{1,32},{TMin,TMax}}},
//#include "fitsShort.c"
//#include "float_abs.c"
//#include "float_f2i.c"
//#include "float_half.c"
//#include "float_i2f.c"
//#include "float_neg.c"
//#include "float_twice.c"
 {"getByte", (funct_t) getByte, (funct_t) test_getByte, 2,
    "! ~ & ^ | + << >>", 6, 2,
  {{TMin, TMax},{0,3},{TMin,TMax}}},
 {"greatestBitPos", (funct_t) greatestBitPos, (funct_t) test_greatestBitPos, 1, "! ~ & ^ | + << >>", 70, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "howManyBits.c"
//#include "ilog2.c"
 {"implication", (funct_t) implication, (funct_t) test_implication, 2, "! ~ ^ |", 5, 2,
     {{0,1},{0,1},{TMin,TMax}}},
 {"isAsciiDigit", (funct_t) isAsciiDigit, (funct_t) test_isAsciiDigit, 1,
    "! ~ & ^ | + << >>", 15, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"isEqual", (funct_t) isEqual, (funct_t) test_isEqual, 2,
    "! ~ & ^ | + << >>", 5, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "isGreater.c"
 {"isLess", (funct_t) isLess, (funct_t) test_isLess, 2,
    "! ~ & ^ | + << >>", 24, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "isLessOrEqual.c"
//#include "isNegative.c"
 {"isNonNegative", (funct_t) isNonNegative, (funct_t) test_isNonNegative, 1,
    "! ~ & ^ | + << >>", 6, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "isNonZero.c"
//#include "isNotEqual.c"
//#include "isPositive.c"
 {"isPower2", (funct_t) isPower2, (funct_t) test_isPower2, 1, "! ~ & ^ | + << >>", 20, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "isTmax.c"
 {"isTmin", (funct_t) isTmin, (funct_t) test_isTmin, 1, "! ~ & ^ | +", 10, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "isZero.c"
//#include "leastBitPos.c"
//#include "leftBitCount.c"
//#include "logicalNeg.c"
//#include "logicalShift.c"
 {"minusOne", (funct_t) minusOne, (funct_t) test_minusOne, 0,
    "! ~ & ^ | + << >>", 2, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//#include "multFiveEighths.c"
//#include "negate.c"
//#include "oddBits.c"
//#include "rempwr2.c"
//#include "replaceByte.c"
//#include "reverseBytes.c"
 {"rotateLeft", (funct_t) rotateLeft, (funct_t) test_rotateLeft,
   2, "! ~ & ^ | + << >>", 25, 3,
  {{TMin, TMax},{0,31},{TMin,TMax}}},
//#include "rotateRight.c"
//#include "satAdd.c"
 {"satMul2", (funct_t) satMul2, (funct_t) test_satMul2, 1,
    "~ & ^ | + << >>", 20, 3,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
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
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
