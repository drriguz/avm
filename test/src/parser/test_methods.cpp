#include "gtest/gtest.h"

#include <iostream>
#include "parser/java_class_parser.h"
#include "parser/class_file_parser.h"

using namespace avm;

TEST(ClassParser, parseSimpleMethod) {
	ClassFileParser parser1("res/com/test/SingleMethod.class");
	const JavaClass javaClass1 = parser1.parse();
	ASSERT_EQ(2, javaClass1.getMethodsCount());


	const MethodInfo* constructor = javaClass1.getMethodAt(0);
	const MethodInfo* hello = javaClass1.getMethodAt(1);
	ASSERT_EQ(6, constructor->getDescriptorIndex());
	ASSERT_EQ(5, constructor->getNameIndex());
	ASSERT_TRUE(constructor->isPublic());

	ASSERT_EQ(10, hello->getDescriptorIndex());
	ASSERT_EQ(9, hello->getNameIndex());

}
