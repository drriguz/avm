#include "gtest/gtest.h"

#include "vm/runtime/vm_field.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(VmField, setAndGetSingleByteValues) {
    VmField field("name", "I");
    field.setInt(1024);
    ASSERT_EQ(1024, field.getInt());
    field.setByte(-12);
    ASSERT_EQ(-12, field.getByte());
    field.setFloat(12.11);
    ASSERT_FLOAT_EQ(12.11, field.getFloat());
}

TEST(VmField, setAndGetDoubleByteValues) {
    VmField field("name", "I");
    field.setLong(10000001);
    ASSERT_EQ(10000001, field.getLong());
    field.setDouble(100000.001);
    ASSERT_EQ(100000.001, field.getDouble());
}