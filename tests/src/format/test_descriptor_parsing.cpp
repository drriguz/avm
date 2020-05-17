#include "gtest/gtest.h"

#include <iostream>
#include "class_file/format/descriptor_type.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(FieldDescriptor, getPrimitiveType) {
    auto f1 = FieldType::fromFieldDescriptor("B");
    ASSERT_EQ(true, f1->isBaseType());
    ASSERT_EQ(false, f1->isArray());
    ASSERT_EQ(FIELD_Byte, ((BaseType*)f1.get())->getType());
}

TEST(FieldDescriptor, getClassType) {
    auto f1 = FieldType::fromFieldDescriptor("Ljava/lang/Sting;");
    ASSERT_EQ(true, f1->isObject());
    ASSERT_EQ(false, f1->isArray());
    ASSERT_STREQ("java/lang/Sting;", ((ObjectType*)f1.get())->getClassName().c_str());
}

TEST(FieldDescriptor, getArrayType) {
    auto f1 = FieldType::fromFieldDescriptor("[Ljava/lang/Sting;");
    ASSERT_EQ(true, f1->isArray());
    auto base = ((ArrayType*)f1.get())->getComponentType();
    ASSERT_EQ(true, base->isObject());
    ASSERT_STREQ("java/lang/Sting;", ((ObjectType*)base)->getClassName().c_str());
}