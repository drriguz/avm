#include "gtest/gtest.h"

#include <iostream>
#include "class_file/format/opcodes.h"

TEST(Opcodes, mapping) {
    Mnemonic nop = static_cast<Mnemonic>(0x00);
    Mnemonic bipush = static_cast<Mnemonic>(0x10);

    ASSERT_EQ(j_nop, nop);
    ASSERT_EQ(j_bipush, bipush);
}