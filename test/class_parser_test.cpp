#include "gtest/gtest.h"

#include "class_parser.h"

using namespace avm;

TEST(Constants, getMagic) {
    ClassParser parser("resources/Complex.class");
    ClassFile parsed = parser.parse();
    ASSERT_EQ(0xCAFEBABE, parsed.getMagic());
}