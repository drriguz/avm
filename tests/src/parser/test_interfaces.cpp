#include "gtest/gtest.h"

#include <iostream>
#include "class_file/parser/java_class_parser.h"

using namespace avm;

TEST(ClassParser, parseClassInterfaces) {
    JavaClassParser parser("res/com/test/MultipleInterfaces.class");
    JavaClass javaClass;
    parser.parse(javaClass);

    ASSERT_EQ(2, javaClass.getInterfacesCount());
    ASSERT_EQ(4, javaClass.getInterfaceAt(0));
    ASSERT_EQ(5, javaClass.getInterfaceAt(1));
}

