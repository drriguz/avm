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
	ASSERT_EQ(76, javaClass.getConstantPoolCount());
}
