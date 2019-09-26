#include "gtest/gtest.h"

#include "class_parser.h"
#include <iostream>

using namespace avm;

ClassFile parseFile(const char *file) {
    ClassParser parser(file);

    try {
        return parser.parse();
    } catch (RuntimeException &ex) {
        std::cout << "Error:" << ex.what() << std::endl;
        throw;
    }
}

TEST(ClassParser, getMagic) {
    ClassFile parsed = parseFile("resources/Complex.class");
    ASSERT_EQ(0xCAFEBABE, parsed.getMagic());
}

TEST(ClassParser, getVersion) {
    ClassFile parsed = parseFile("resources/Complex.class");
    ASSERT_EQ(52, parsed.getMajorVersion());
    ASSERT_EQ(0, parsed.getMinorVersion());
}

TEST(ClassParser, parseUnknownFile) {
    try {
        ClassFile parsed = parseFile("resources/1.txt");
        FAIL() << "Expected exception";
    } catch (const NotClassFileException& ex) {
        std::cout << "~~" << ex.what() << std::endl;
    } catch (...) {
        std::cout << "!~"  << std::endl;
        FAIL() << "Expected exception but the type is not expected";
    }
}