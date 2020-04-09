#include "gtest/gtest.h"

#include <iostream>
#include "class_file/parser/java_class_parser.h"

using namespace avm;

TEST(ClassParser, getConstants) {
    JavaClassParser parser("res/com/test/Constants.class");
    JavaClass javaClass;
    parser.parse(javaClass);
    ASSERT_EQ(93, javaClass.getConstantPoolCount());

    const ConstantClass *c1 = (ConstantClass*) javaClass.getConstantAt(15);
    ASSERT_EQ(65, c1->getNameIndex());

    const ConstantFieldref *c2 = (ConstantFieldref*) javaClass.getConstantAt(3);
    ASSERT_EQ(21, c2->getClassIndex());
    ASSERT_EQ(53, c2->getNameAndTypeIndex());

    const ConstantMethodref *c3 = (ConstantMethodref*) javaClass.getConstantAt(
            1);
    ASSERT_EQ(22, c3->getClassIndex());
    ASSERT_EQ(51, c3->getNameAndTypeIndex());

    const ConstantInterfaceMethodref *c4 =
            (ConstantInterfaceMethodref*) javaClass.getConstantAt(19);
    ASSERT_EQ(68, c4->getClassIndex());
    ASSERT_EQ(69, c4->getNameAndTypeIndex());

    const ConstantString *c5 = (ConstantString*) javaClass.getConstantAt(2);
    ASSERT_EQ(52, c5->getStringIndex());

    const ConstantInteger *c6 = (ConstantInteger*) javaClass.getConstantAt(30);
    ASSERT_EQ(1024, c6->getValue());

    const ConstantFloat *c7 = (ConstantFloat*) javaClass.getConstantAt(4);
    ASSERT_EQ(3.1415926f, c7->getValue());

    const ConstantLong *c8 = (ConstantLong*) javaClass.getConstantAt(7);
    ASSERT_EQ(299792458l, c8->getValue());

    const ConstantDouble *c10 = (ConstantDouble*) javaClass.getConstantAt(10);
    ASSERT_EQ(3.1415926535898, c10->getValue());

    const ConstantNameAndType *c11 =
            (ConstantNameAndType*) javaClass.getConstantAt(51);
    ASSERT_EQ(42, c11->getNameIndex());
    ASSERT_EQ(43, c11->getDescriptorIndex());

    const ConstantUtf8 *c12 = (ConstantUtf8*) javaClass.getConstantAt(23);
    ASSERT_STREQ("str", c12->getValue().c_str());

    const ConstantMethodHandle *c13 =
            (ConstantMethodHandle*) javaClass.getConstantAt(59);
    ASSERT_EQ(6, c13->getReferenceKind());
    ASSERT_EQ(73, c13->getReferenceIndex());

    const ConstantMethodType *c14 =
            (ConstantMethodType*) javaClass.getConstantAt(62);
    ASSERT_EQ(48, c14->getDescriptorIndex());

    const ConstantInvokeDynamic *c15 =
            (ConstantInvokeDynamic*) javaClass.getConstantAt(13);
    ASSERT_EQ(0, c15->getBootstrapMethodAttrIndex());
    ASSERT_EQ(63, c15->getNameAndTypeIndex());
}

