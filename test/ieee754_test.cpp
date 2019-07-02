#include "gtest/gtest.h"

#include "format/constants.h"
#include "utils/ieee754.h"

using namespace avm;

TEST(IEEE754Helper, parseFloat) {
    char result[33];
    IEEE754Helper::print(0.8f, result);
    ASSERT_STREQ("00111111010011001100110011001101", result);
    IEEE754Helper::print(0.9f, result);
    ASSERT_STREQ("00111111011001100110011001100110", result);
    IEEE754Helper::print(1.0f, result);
    ASSERT_STREQ("00111111100000000000000000000000", result);
    IEEE754Helper::print(3.14f, result);
    ASSERT_STREQ("01000000010010001111010111000011", result);
}

TEST(ConstantFloat, getFloatValue) {
    ConstantFloat f1 = {0x4048f5c3};
    ConstantFloat f2 = {0x3f800000};
    ConstantFloat f3 = {0x40490fda};
    ASSERT_EQ(3.14f, f1.getValue());
    ASSERT_EQ(1.0f, f2.getValue());
    ASSERT_EQ(3.1415926f, f3.getValue());
}

TEST(ConstantFloat, getDoubleValue) {
    
}