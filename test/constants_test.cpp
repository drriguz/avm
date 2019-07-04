#include "gtest/gtest.h"

#include "format/constants.h"
#include "utils/ieee754.h"

using namespace avm;

TEST(Constants, getFloatValue) {
    ConstantFloat f1 = {0x4048f5c3};
    ConstantFloat f2 = {0x3f800000};
    ConstantFloat f3 = {0x40490fda};
    ASSERT_EQ(3.14f, f1.getValue());
    ASSERT_EQ(1.0f, f2.getValue());
    ASSERT_EQ(3.1415926f, f3.getValue());
}

TEST(Constants, getLongValue) {
    ConstantLong l1 = {0x0C56ADD0, 0xDC2F040D};
    ConstantLong l2 = {0x00000000, 0x00006E45};
    ASSERT_EQ(889089089011123213l, l1.getValue());
    ASSERT_EQ(28229l, l2.getValue());
}

TEST(Constants, getDoubleValue) {
    ConstantDouble d1 = {0x40270000, 0x00000000};
    ConstantDouble d2 = {0x419D6F34, 0x57F35BA8};
    ASSERT_EQ(11.5, d1.getValue());
    ASSERT_EQ(123456789.987654321, d2.getValue());
}