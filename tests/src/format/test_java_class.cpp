#include "gtest/gtest.h"

#include <iostream>
#include "class_file/parser/java_class_parser.h"
#include "class_file/format/java_class.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(JavaClass, getMethodIfFound) {
    JavaClassParser parser1("res/com/test/SingleMethod.class");
    JavaClass javaClass1;
    parser1.parse(javaClass1);

    const MethodInfo *hello = javaClass1.getMethod("hello",
            "()Ljava/lang/String;");
    ASSERT_STREQ("hello", hello->getName().c_str());
    ASSERT_STREQ("()Ljava/lang/String;", hello->getDescriptor().c_str());
}

TEST(JavaClass, getMethodWithFlagsIfFound) {
    JavaClassParser parser1("res/com/vm/HelloWorld.class");
    JavaClass javaClass1;
    parser1.parse(javaClass1);

    const MethodInfo *hello = javaClass1.getMethod("main",
            "([Ljava/lang/String;)V", 2, ACC_PUBLIC, ACC_STATIC);
    ASSERT_STREQ("main", hello->getName().c_str());
}

TEST(JavaClass, throwExceptionIfNotFound) {
    JavaClassParser parser1("res/com/test/SingleMethod.class");
    JavaClass javaClass1;
    parser1.parse(javaClass1);

    EXPECT_THROW(javaClass1.getMethod("hello", "()Ljava/lang/Number;"),
            MethodNotFoundException);
    EXPECT_THROW(
            javaClass1.getMethod("hello", "()Ljava/lang/String;", 1, ACC_STATIC),
            MethodNotFoundException);
    EXPECT_THROW(
            javaClass1.getMethod("hello", "()Ljava/lang/String;", 2, ACC_PUBLIC, ACC_STATIC),
            MethodNotFoundException);
    EXPECT_THROW(javaClass1.getMethod("world", "()Ljava/lang/String;"),
            MethodNotFoundException);
}
