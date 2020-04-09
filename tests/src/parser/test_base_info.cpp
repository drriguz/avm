#include "gtest/gtest.h"

#include <iostream>
#include "class_file/parser/java_class_parser.h"

using namespace avm;

TEST(ClassParser, getMetaInfo) {
    JavaClassParser parser("res/com/test/Simple.class");
    JavaClass javaClass;
    parser.parse(javaClass);
    ASSERT_EQ(0xCAFEBABE, javaClass.getMagic());
    ASSERT_EQ(52, javaClass.getMajorVersion());
    ASSERT_EQ(0, javaClass.getMinorVersion());
}

TEST(ClassParser, parseClassMultipleTimes) {
    JavaClassParser parser("res/com/test/Simple.class");
    JavaClass javaClass;
    parser.parse(javaClass);
    parser.parse(javaClass);
    parser.parse(javaClass);
    ASSERT_EQ(0xCAFEBABE, javaClass.getMagic());
}

TEST(ClassParser, parseClassDescriptors) {
    JavaClassParser parser("res/com/test/Simple.class");
    JavaClass javaClass;
    parser.parse(javaClass);
    ASSERT_TRUE(javaClass.isPublic());
    ASSERT_TRUE(javaClass.isSuper());
    ASSERT_FALSE(javaClass.isFinal());
    ASSERT_FALSE(javaClass.isSynthetic());

    ASSERT_EQ(2, javaClass.getThisClass());
    ASSERT_EQ(3, javaClass.getSuperClass());
}
