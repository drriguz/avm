#include "gtest/gtest.h"

#include <iostream>
#include "parser/java_class_parser.h"
#include "parser/class_file_parser.h"

using namespace avm;

TEST(ClassParser, getMetaInfo) {
	ClassFileParser parser("res/com/test/Simple.class");
	const JavaClass javaClass = parser.parse();
	ASSERT_EQ(0xCAFEBABE, javaClass.getMagic());
	ASSERT_EQ(52, javaClass.getMajorVersion());
	ASSERT_EQ(0, javaClass.getMinorVersion());
}

TEST(ClassParser, parseClassMultipleTimes) {
	ClassFileParser parser("res/com/test/Simple.class");
	parser.parse();
	parser.parse();
	const JavaClass javaClass = parser.parse();
	ASSERT_EQ(0xCAFEBABE, javaClass.getMagic());
}

TEST(ClassParser, getConstants) {
	ClassFileParser parser("res/com/test/Constants.class");
	const JavaClass javaClass = parser.parse();
	ASSERT_EQ(93, javaClass.getConstantPoolCount());

	const ConstantClass* c1 = (ConstantClass*)javaClass.getConstantAt(15)->info;
	ASSERT_EQ(65, c1->nameIndex);

	const ConstantFieldref* c2 = (ConstantFieldref*)javaClass.getConstantAt(3)->info;
	ASSERT_EQ(21, c2->classIndex);
	ASSERT_EQ(53, c2->nameAndTypeIndex);

	const ConstantMethodref* c3 = (ConstantMethodref*)javaClass.getConstantAt(1)->info;
	ASSERT_EQ(22, c3->classIndex);
	ASSERT_EQ(51, c3->nameAndTypeIndex);

	const ConstantInterfaceMethodref* c4 = (ConstantInterfaceMethodref*)javaClass.getConstantAt(19)->info;
	ASSERT_EQ(68, c4->classIndex);
	ASSERT_EQ(69, c4->nameAndTypeIndex);

	const ConstantString* c5 = (ConstantString*)javaClass.getConstantAt(2)->info;
	ASSERT_EQ(52, c5->stringIndex);

	const ConstantInteger* c6 = (ConstantInteger*)javaClass.getConstantAt(30)->info;
	ASSERT_EQ(1024, c6->bytes);

	const ConstantFloat* c7 = (ConstantFloat*)javaClass.getConstantAt(4)->info;
	ASSERT_EQ(3.1415926f, c7->getValue());

	const ConstantLong* c8 = (ConstantLong*)javaClass.getConstantAt(7)->info;
	ASSERT_EQ(299792458l, c8->getValue());

	const ConstantDouble* c10 = (ConstantDouble*)javaClass.getConstantAt(10)->info;
	ASSERT_EQ(3.1415926535898, c10->getValue());

	const ConstantNameAndType* c11 = (ConstantNameAndType*)javaClass.getConstantAt(51)->info;
	ASSERT_EQ(42, c11->nameIndex);
	ASSERT_EQ(43, c11->descriptorIndex);

	const ConstantUtf8* c12 = (ConstantUtf8*)javaClass.getConstantAt(23)->info;
	ASSERT_STREQ("str", (char*)c12->bytes);

	const ConstantMethodHandle* c13 = (ConstantMethodHandle*)javaClass.getConstantAt(59)->info;
	ASSERT_EQ(6, c13->referenceKind);
	ASSERT_EQ(73, c13->referenceIndex);

	const ConstantMethodType* c14 = (ConstantMethodType*)javaClass.getConstantAt(62)->info;
	ASSERT_EQ(48, c14->descriptorIndex);


	const ConstantInvokeDynamic* c15 = (ConstantInvokeDynamic*)javaClass.getConstantAt(13)->info;
	ASSERT_EQ(0, c15->bootstrapMethodAttrIndex);
	ASSERT_EQ(63, c15->nameAndTypeIndex);
}

TEST(ClassParser, parseClassDescriptors) {
	ClassFileParser parser("res/com/test/Simple.class");
	const JavaClass javaClass = parser.parse();
	ASSERT_TRUE(javaClass.isPublic());
	ASSERT_TRUE(javaClass.isSuper());
	ASSERT_FALSE(javaClass.isFinal());
	ASSERT_FALSE(javaClass.isSynthetic());

	ASSERT_EQ(2, javaClass.getThisClass());
	ASSERT_EQ(3, javaClass.getSuperClass());
}

TEST(ClassParser, parseClassInterfaces) {
	ClassFileParser parser("res/com/test/MultipleInterfaces.class");
	const JavaClass javaClass = parser.parse();

	ASSERT_EQ(2, javaClass.getInterfacesCount());
	ASSERT_EQ(4, javaClass.getInterfaceAt(0));
	ASSERT_EQ(5, javaClass.getInterfaceAt(1));
}
