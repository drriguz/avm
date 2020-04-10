#include "gtest/gtest.h"

#include <iostream>
#include "class_file/parser/java_class_parser.h"

using namespace avm;

TEST(ClassParser, parseSimpleMethod) {
    JavaClassParser parser1("res/com/test/SingleMethod.class");
    JavaClass javaClass1;
    parser1.parse(javaClass1);
    ASSERT_EQ(2, javaClass1.getMethodsCount());

    const MethodInfo *constructor = javaClass1.getMethodAt(0);
    const MethodInfo *hello = javaClass1.getMethodAt(1);
    ASSERT_EQ(6, constructor->getDescriptorIndex());
    ASSERT_EQ(5, constructor->getNameIndex());
    ASSERT_TRUE(constructor->isPublic());

    ASSERT_EQ(10, hello->getDescriptorIndex());
    ASSERT_EQ(9, hello->getNameIndex());
    ASSERT_STREQ("hello", hello->getName().c_str());
    ASSERT_STREQ("()Ljava/lang/String;", hello->getDescriptor().c_str());
}

TEST(ClassParser, methodCodeAttribute) {
    JavaClassParser parser1("res/com/vm/HelloWorld.class");
    JavaClass javaClass1;
    parser1.parse(javaClass1);
    ASSERT_EQ(2, javaClass1.getMethodsCount());

    const MethodInfo *constructor = javaClass1.getMethodAt(0);
    const MethodInfo *hello = javaClass1.getMethodAt(1);
    ASSERT_EQ(1, constructor->getCode()->getMaxLocals());
    ASSERT_EQ(1, constructor->getCode()->getMaxStack());
    ASSERT_EQ(4, hello->getCode()->getMaxLocals());
    ASSERT_EQ(3, hello->getCode()->getMaxStack());
}