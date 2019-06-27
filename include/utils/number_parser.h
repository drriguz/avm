#ifndef _AVM_NUMBER_PARSER_H_
#define _AVM_NUMBER_PARSER_H_

#include "../format/constants.h"

namespace avm {
  class NumberParser{
  public:
    static float parseFloat(const ConstantFloat& raw);
    static double parseDouble();
  };
}

#endif
