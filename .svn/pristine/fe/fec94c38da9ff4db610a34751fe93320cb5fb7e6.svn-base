/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    /* get_sign gives you either 1111...1111 or 0000...0000
     * get_value gives you the unchanged x if get_sign is 0000...
     * and the two's complement x if get sign is negative 1111...
     * xor with zeroes for positive does nothing
     * xor with ones for negative swaps 0's and 1's (works like ~)
     */
    int get_sign = x >> 31;
    int get_value = x + get_sign;
    return get_sign ^ get_value;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    /* if signs of x and y are the same, but sign
     * of x and x + y are different -> overflow
     */
    int x_mask = x >> 31;
    int y_mask = y >> 31;
    int xy_mask = (x + y) >> 31;
    return !(!(x_mask ^ y_mask) & !!(x_mask ^ xy_mask));
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
    /* create 1010...1010, then or it with x to get 1111...1111
     * ~ of this gives 0000...0000 and the ! gives 1
     */
    int half_odd = (0xAA << 8) | 0xAA;
    int all_odd = (half_odd << 16) | half_odd;
    return !~(all_odd | x);
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    /* if x != 0, then x or -x will have a one in
     * the most signficant bit, adding 1 to 1111...1111 = 0
     * while adding 1 to 0000...0000 = 1
     */
    int check_one = (x | (~x + 1)) >> 31;
    return check_one + 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    /* Couldn't figure this one out
     */
    return 0;
}
/*
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    return (~x) & (~y);
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) { 
    /* isolate each individual byte in the least significant byte
     * swap the two bytes and mask them into the original x using xor
     */
    int n_bits = n << 3;
    int m_bits = m << 3;
    
    int x_n = (x >> m_bits) & 0xFF;
    int x_m = (x >> n_bits) & 0xFF;

    int mask = x_n ^ x_m;
    
    return x ^ (mask << n_bits) ^ (mask << m_bits);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /* if x = 0 -> x = 0000...0000 or if x = 1 -> x = 1111...1111
     * if x = 1 -> x & y = y and the other will be 0
     * if x = 0 -> ~x & z = z and the other will be 0
     */
    x = ~(!!x) + 1;
    return (x & y) | (~x & z);
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
    /* Multiply x by 3 and get its sign
     * 011 & sign of x*3, if negative will add the overflow to x*3
     * Divide by 4
     */
    int x_3 = (x << 1) + x;
    int sign_x_3 = x_3 >> 31;
    int account_for_overflow = (0b11) & (sign_x_3);
    return (x_3 + account_for_overflow) >> 2;
}
/* 
 * fitsBits - return 1 if x can be represented as an
    int sign_x = x >> 31;

    int x_neg = (x_3 >> 2) & (~sign_x);
    int x_pos = (x_3 >> 2 + 1) & (sign_x);

    return x_neg | x_pos; 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    // 32 - n = 32 + (-n) = 32 + (~n + 1) = 33 + ~n
    // this is done because you can't use a minus sign
    // fill in the higher order bits and then check if x == this
    int complement = 33 + ~n;
    int fill_higher_bits = (x << complement) >> complement;
    return !(fill_higher_bits ^ x);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    /* move x down 8n, for n in [0, 3]
     * grab the least significant byte
     */
    return x >> (n << 3) & 0xFF;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
    /* get the main digit and then make everything after it a one
     * reverse this and shift it by one to isolate the main digit
     * save the sign digit in case it is isolated
     */
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4); 
    x = x | (x >> 8); 
    x = x | (x >> 16);
    return x & ((~x >> 1) ^ (1 << 31));
}
/*
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    /* must add !(x ^ y) in case both x and y are 1111...1111
     */
    return (!(x ^ y)) | y;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /* 0x39 is 57 in decimal -> 0x3A is 58 in decimal
     * 0x30 is 48 in decimal -> 0x2F is 47 in decimal
     * if lower_sign = 1111...: x >= 0x30 (F)
     * if lower_sign = 0000...: x >= 0x30 (T)
     * if upper_sign = 1111...: x <= 0x39 (F)
     * if upper_sign = 0000...: x <= 0x39 (T)
     * If they are both true then it will return 1
     */
    
    int lower = x + (~0x2F);
    int lower_sign = lower >> 31;
    int upper = 0x3A + (~x);
    int upper_sign = upper >> 31;
    return !(upper_sign | lower_sign);
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    /* bitwise or is always 0 when the two numbers are equal
     */
    return !(x ^ y);
}
/*
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
    /* x < y if:
     * x is negative and y is positive
     * x and y have the same sign, but x - y is negative
     * | these two together and you can check if x < y
     */
    int x_minus_y = x + ~y + 1;
    
    int sign_of_x = x >> 31;
    int sign_of_y = y >> 31;
    int case1 = sign_of_x & ~sign_of_y;
    int case2 = (~(sign_of_x ^ sign_of_y)) & (x_minus_y >> 31);

    return !!(case1 | case2);
}
/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
    /* shift sign digit all the way to the right
     * & it with one and reverse it to show that the number is negative
     */
    int digit = x >> 31 & 0b1;
    return !digit;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
    /* check if x is not zero and if x is not negative
     * power of 2 - 1 is always many leading ones up to the 2's digit
     * if you and those together you should get all zeros, this is the
     * subtract flag
     */
    int not_zero = !!x;
    int not_negative = !(x >> 31 & 0b1);
    int subtract_flag = !(x & (x + ~1 + 1));
    return not_zero & not_negative & subtract_flag;
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
    /* minimum twos complement number is 1000...0000
     * x + x = 0 due to overflow, but 0 + 0 also = 0
     * But flipping 0 = 1, while flipping 1 = 0
     */
    return !(x + x) & !!x;
}
/*
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
    // this is just basic two's complement on the number 1
    return ~1 + 1;
}
/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
    /* get the last n masked with ones, shift them to the end
     * 
     * apply the mask to x and then shift it all back
     * if the number is negative, remove the leading ones
     * shift the bulk of the binary number to the left n
     * & it with the newly shifted ending
     */
    int end_mask = ~((~0) << n);
    int first_mask = end_mask << (32 - n);

    int last_n = ((x & first_mask) >> (32 - n));
    int remove_leading_ones = last_n & end_mask;
    return (x << n) | remove_leading_ones;
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
    /* positive overflow -> leading 0 turns into leading 1 -> return TMax
     * negative overflow -> leading 1 turns into leading 0 -> return TMin
     * Find the signs of x and x*2, saturate if need be
     */
    int t_max = ~(1 << 31);

    int sign_x = x >> 31;
    int x_2 = x << 1;
    int sign_x_2 = (x ^ x_2) >> 31;

    int saturate = (sign_x ^ t_max) & (sign_x_2);
    return (~sign_x_2 & x_2) | saturate;
}

