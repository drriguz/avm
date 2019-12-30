#include "gtest/gtest.h"

#include <iostream>
#include "parser/java_class_parser.h"
#include "parser/class_file_parser.h"

using namespace avm;

TEST(ClassParser, parseSimpleFields) {
	ClassFileParser parser("res/com/test/Simple.class");
	const JavaClass javaClass = parser.parse();

	ASSERT_EQ(0, javaClass.getFieldsCount());

	ClassFileParser parser1("res/com/test/SingleField.class");
	const JavaClass javaClass1 = parser1.parse();

	ASSERT_EQ(1, javaClass1.getFieldsCount());
	const FieldInfo* field = javaClass1.getFieldAt(0);
	ASSERT_TRUE(field->isPublic());
	ASSERT_TRUE(field->isStatic());
	ASSERT_FALSE(field->isEnum());
}

