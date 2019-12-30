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
