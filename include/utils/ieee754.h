#ifndef _AVM_NUMBER_PARSER_H_
#define _AVM_NUMBER_PARSER_H_

#include "../format/constants.h"

#include <string>

namespace avm {
  /**
   * f = 3.14
   * Low                            High
   * ---------------------------------->
   * 01000000 01001000 11110101 11000011 [big endian]
   * 0x40     0x48     0xf5     0xc3
   *
   * 11000011 11110101 01001000 01000000 [little-endian]
   * 0xc3     0xf5     0x48     0x40
   *
   * ieee754:
   * 0|10000000|10010001111010111000011
   */
  
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
    double value;
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
  };
} // namespace avm

#endif
