#ifndef _AVM_NUMBER_PARSER_H_
#define _AVM_NUMBER_PARSER_H_

#include "../format/constants.h"

#include <string>

namespace avm {
  typedef union {
    float value;
    struct
    {
      unsigned int mantissa : 23;
      unsigned int exponent : 8;
      unsigned int sign : 1;

    } raw;
  } IEEE754Float;

  typedef union {
    float value;
    struct
    {
      unsigned long mantissa : 52;
      unsigned int exponent : 11;
      unsigned int sign : 1;

    } raw;
  } IEEE754Double;

  class IEEE754Helper {
  private:
    IEEE754Helper() {}

  public:
    static void print(const float &number, char result[32 + 1]);
    static void print(const double &number, char result[64 + 1]);

  private:
    static void printBinary(long raw, int width);
  };
} // namespace avm

#endif
