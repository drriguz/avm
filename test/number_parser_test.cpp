#include "gtest/gtest.h"

#include "format/constants.h"
#include "utils/number_parser.h"

using namespace avm;


TEST(NumberParser, parseFloat){
  const ConstantFloat f1 = {0x3f4ccccd};
  const ConstantFloat f2 = {0x3f666666};
  const ConstantFloat f3 = {0x3f800000};
  ASSERT_EQ(0.8f, NumberParser::parseFloat(f1));
  ASSERT_EQ(0.9f, NumberParser::parseFloat(f2));
  ASSERT_EQ(1.0f, NumberParser::parseFloat(f3));
}