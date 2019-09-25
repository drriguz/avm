#include "gtest/gtest.h"

#include "class_parser.h"
#include <iostream>

using namespace avm;

ClassFile *parseFile(const char *file) {
    ClassParser parser(file);
    ClassFile *parsed;
    try {
        parsed = parser.parse();
    } catch (RuntimeException &ex) {
        std::cout << "Error:" << ex.what() << std::endl;
    }
    return parsed;
}

TEST(ClassParser, getMagic) {
    ClassFile *parsed = parseFile("resources/Complex.class");
    ASSERT_EQ(0xCAFEBABE, parsed->getMagic());
    delete parsed;
}

TEST(ClassParser, getVersion) {
    ClassFile *parsed = parseFile("resources/Complex.class");
    ASSERT_EQ(52, parsed->getMajorVersion());
    ASSERT_EQ(0, parsed->getMinorVersion());
    delete parsed;
}