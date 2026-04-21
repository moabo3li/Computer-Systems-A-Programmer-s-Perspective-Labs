/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
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

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // build XOR from NAND gates: ~(x&y) blocks the both-1 case,
  // then two more NANDs isolate each exclusive set, a final NAND merges them
  int notBoth = ~(x & y);
  int xOnly = ~(notBoth & x);
  int yOnly = ~(notBoth & y);
  int xorResult = ~(yOnly & xOnly);
  return xorResult;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //  shift the sign bit into position; all other bits 0 gives the most negative
  //  value
  return (1 << 31);
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // Tmax+1 == Tmin, and Tmax+Tmin == 0xFFFFFFFF so ~(x+(x+1)) == 0 only for
  // Tmax; !!plusOne guards against x==-1 which also satisfies the sum condition
  int plusOne = x + 1;
  x = x + plusOne;
  x = ~x;
  return !x & !!plusOne;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // build 0xAAAAAAAA by byte-replication of 0xAA (constants > 0xFF are
  // forbidden), then mask x to odd bits and XOR with mask; result is 0 iff all
  // odd bits were 1
  int mask = 0xAA;
  mask = (mask << 8) | mask;
  mask = (mask << 16) | mask;
  return !((x & mask) ^ mask);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // two's complement negation: flip all bits to get ~x, then add 1
  return (~x) + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // subtract 0x30 from x; if result is negative, x is below the range
  // subtract x from 0x39; if result is negative, x is above the range
  // both differences must be non-negative (sign bit == 0) for x to be a digit
  int aboveMin = !((x + (~0x30) + 1) >> 31);
  int belowMax = !((0x39 + (~x) + 1) >> 31);
  return aboveMin & belowMax;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // normalize x to 0 or 1, then expand to all-0s / all-1s selection mask:
  // selMask is 0xFFFFFFFF when x != 0 (selects y), 0x00000000 when x == 0
  // (selects z)
  int xBool = !!x;
  int selMask = (~xBool) + 1;
  return (y & selMask) | (z & ~selMask);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // split into two cases to avoid signed overflow when computing y - x:
  // case 1: signs differ  -> x <= y iff x is negative (signX == 1)
  // case 2: signs equal   -> x <= y iff y - x >= 0 (sign bit of diff is 0)
  int signX = (x >> 31) & 1;
  int signY = (y >> 31) & 1;
  int diff = y + (~x + 1);
  int signDiff = (diff >> 31) & 1;
  int signsDiffer = signX ^ signY;
  return (signsDiffer & signX) | (!signsDiffer & !signDiff);
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  /* OR x with its negation sets the sign bit for any x!=0; arithmetic
     right-shift by 31 gives all-1s (-1) for x!=0 and 0 for x==0;
     adding 1 maps those to 0 and 1 respectively, implementing ! */
  int orWithNeg = x | (~x + 1);
  int signMask = orWithNeg >> 31;
  return signMask + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* flip negative x to positive so we only need to find the highest 1-bit;
     then use binary search (halving the search space each step) to count
     how many bits that highest 1-bit sits at; +1 for the sign bit */
  int b16, b8, b4, b2, b1, b0;

  int sign = x >> 31;
  x = (sign & ~x) | (~sign & x);

  b16 = !!(x >> 16) << 4;
  x >>= b16;
  b8 = !!(x >> 8) << 3;
  x >>= b8;
  b4 = !!(x >> 4) << 2;
  x >>= b4;
  b2 = !!(x >> 2) << 1;
  x >>= b2;
  b1 = !!(x >> 1);
  x >>= b1;
  b0 = x;

  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {

  // intput's format
  unsigned sign_uf = uf & 0x80000000;
  unsigned exp_uf = (uf >> 23) & 0xff;
  unsigned frac_uf = (uf & 0x7fffff);

  // NAN or Infinity
  if (exp_uf == 0xff)
    return uf;

  // Denormalized number
  if (exp_uf == 0) {
    frac_uf <<= 1;
    return sign_uf | frac_uf;
  }

  // Normalized number
  exp_uf += 1;
  return sign_uf | (exp_uf << 23) | frac_uf;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {

  // intput's format
  unsigned sign_uf = uf >> 31;
  unsigned exp_uf = (uf >> 23) & 0xff;
  unsigned frac_uf = (uf & 0x7fffff);
  // Set the E
  int E = exp_uf - 127;
  int M = (0x800000 | frac_uf);

  if (E < 0) {
    return 0;
  }

  if (E >= 31) {
    return 0x80000000u;
  }

  if (E > 23) {
    M = M << (E - 23);
  } else {
    M = M >> (23 - E);
  }

  if (sign_uf) {
    return -M;
  }

  // set the sign bit
  return M;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {

  if (x > 127) {
    return 0x7F800000;
  }

  if (x < -149) {
    return 0;
  }

  if (x >= -126) {
    int exp = x + 127;
    return exp << 23;
  }

  return 1 << (x + 149);
}
