#include "gtest/gtest.h"

#include <iostream>
#include <fstream>

#include "class_file/parser/binary_reader.h"

using namespace avm;

TEST(BinaryReader, readBigEndian) {
    BinaryReader reader("res/test-endian.bin");
    u4 magic;
    u2 minorVersion, majorVersion, constantCount;
    reader.readU4(&magic);
    reader.readU2(&minorVersion);
    reader.readU2(&majorVersion);
    reader.readU2(&constantCount);

    ASSERT_EQ(0xCAFEBABE, magic);
    ASSERT_EQ(0, minorVersion);
    ASSERT_EQ(0x34, majorVersion);
    ASSERT_EQ(0x12, constantCount);
}

TEST(BinaryReader, skip) {
	BinaryReader reader("res/test-endian.bin");
    u2 minorVersion, constantCount;
    reader.skip(4);
    reader.readU2(&minorVersion);
    reader.skip(2);
    reader.readU2(&constantCount);

    ASSERT_EQ(0, minorVersion);
    ASSERT_EQ(0x12, constantCount);
}
