#include "gtest/gtest.h"

#include <iostream>
#include "class_file/format/constant/number.h"

#include "class_file/exceptions.h"

#include "vm/runtime/slot.h"

using namespace avm;

TEST(ConstantNumber, getValue) {
    ConstantDouble number(0x400921FB, 0x54442d28);
    ASSERT_EQ(3.1415926535898, number.getValue());
}

TEST(Misc, ReferenceSize) {
#ifdef _ARCH_X64_
    ASSERT_EQ(8, sizeof(reference));
#else
    ASSERT_EQ(4, sizeof(reference));
#endif
}