#include "utils/ieee754.h"

#include <iostream>
#include <stdlib.h>

using namespace avm;

inline char convert(unsigned int bit) {
  return (bit & 1) ? '1' : '0';
}

inline void printBits(const long &raw, const int &width, char out[32 + 1], int start) {
  for (int k = width - 1, i = start; k >= 0; k--, i++) {
    char it = convert(raw >> k);
    out[i] = it;
  }
}

void IEEE754Helper::print(const float &number, char result[32 + 1]) {
  IEEE754Float f;
  f.value = number;
  result[0] = convert(f.raw.sign);
  printBits(f.raw.exponent, 8, result, 1);
  printBits(f.raw.mantissa, 23, result, 9);
  result[32] = '\0';
}

void IEEE754Helper::print(const double &number, char result[64 + 1]) {
  IEEE754Double d;
  d.value = number;
  result[0] = convert(d.raw.sign);
  printBits(d.raw.exponent, 11, result, 1);
  printBits(d.raw.mantissa, 52, result, 12);
  result[64] = '\0';
}
