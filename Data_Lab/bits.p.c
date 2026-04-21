#line 144 "bits.c"
int bitXor(int x, int y) {
#line 149
  int xynand=  ~(x & y);
  int xnand=  ~(xynand & x);
  int bnand=  ~(xynand & y);
  int resnand=  ~(bnand & xnand);

  return resnand;
}
#line 162
int tmin(void) { return 2; }
#line 171
int isTmax(int x) { return 2; }
#line 180
int allOddBits(int x) { return 2; }
#line 188
int negate(int x) { return 2; }
#line 198
int isAsciiDigit(int x) { return 2; }
#line 206
int conditional(int x, int y, int z) { return 2; }
#line 214
int isLessOrEqual(int x, int y) { return 2; }
#line 224
int logicalNeg(int x) { return 2; }
#line 237
int howManyBits(int x) { return 0; }
#line 250
unsigned floatScale2(unsigned uf) { return 2; }
#line 263
int floatFloat2Int(unsigned uf) { return 2; }
#line 277
unsigned floatPower2(int x) { return 2; }
