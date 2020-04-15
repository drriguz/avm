#include "gtest/gtest.h"

#include <iostream>
#include "class_file/format/descriptor_type.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(FieldDescriptor, getPrimitiveType) {
    FieldDescriptor f1("B");
    ASSERT_EQ(Byte, f1.getBaseType());
    ASSERT_EQ(false, f1.isArray());
    ASSERT_STREQ("", f1.getClassName().c_str());
}

TEST(FieldDescriptor, getClassType) {
    FieldDescriptor f1("Ljava/lang/Sting;");
    ASSERT_EQ(Reference, f1.getBaseType());
    ASSERT_EQ(false, f1.isArray());
    ASSERT_STREQ("java/lang/Sting;", f1.getClassName().c_str());
}

TEST(FieldDescriptor, getArrayType) {
    FieldDescriptor f1("[Ljava/lang/Sting;");
    ASSERT_EQ(Reference, f1.getBaseType());
    ASSERT_EQ(true, f1.isArray());
    ASSERT_STREQ("java/lang/Sting;", f1.getClassName().c_str());
}