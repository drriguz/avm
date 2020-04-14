#include "gtest/gtest.h"

#include "vm/runtime/local_variables.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(LocalVariables, saveAndGetSingleByteValues) {
    LocalVariables var(5);
    var.setByte(0, 18);
    ASSERT_EQ(18, var.getByte(0));
    var.setByte(0, 20);
    ASSERT_EQ(20, var.getByte(0));
    var.setShort(0, 18);
    ASSERT_EQ(18, var.getShort(0));
    var.setInt(0, 1234);
    ASSERT_EQ(1234, var.getInt(0));
    var.setFloat(0, 1234.65);
    ASSERT_FLOAT_EQ(1234.65, var.getFloat(0));
}

TEST(LocalVariables, saveAndGetDoubleByteValues) {
    LocalVariables var(5);
    var.setLong(0, 100000010001);
    var.setDouble(2, 100000000.88);
    var.setInt(4, 18);
    ASSERT_EQ(100000010001, var.getLong(0));
    ASSERT_EQ(100000000.88, var.getDouble(2));
    ASSERT_EQ(18, var.getInt(4));
}

TEST(LocalVariables, saveAndGetNegativeByteValues) {
    LocalVariables var(5);
    var.setLong(0, -100000010001);
    var.setDouble(2, -100000000.88);
    var.setInt(4, -18);
    ASSERT_EQ(-100000010001, var.getLong(0));
    ASSERT_EQ(-100000000.88, var.getDouble(2));
    ASSERT_EQ(-18, var.getInt(4));
}

TEST(LocalVariables, throwExceptionIfOutOfRange) {
    LocalVariables var(1);

    EXPECT_THROW(var.setLong(0, -100000010001),
                 LocalVariablesOutOfRangeException);
    EXPECT_THROW(var.setLong(2, -100000010001),
                 LocalVariablesOutOfRangeException);
}
