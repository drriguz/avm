#include "gtest/gtest.h"

#include <iostream>
#include "class_file/parser/java_class_parser.h"
#include "class_file/parser/class_file_parser.h"
#include "class_file/format/java_class.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(JavaClass, getMethodIfFound) {
	ClassFileParser parser1("res/com/test/SingleMethod.class");
	JavaClass javaClass1;
	parser1.parse(javaClass1);

	const MethodInfo* hello = javaClass1.getMethod("hello", "()Ljava/lang/String;");
	ASSERT_STREQ("hello", hello->getName().c_str());
	ASSERT_STREQ("()Ljava/lang/String;", hello->getDescriptor().c_str());
}

TEST(JavaClass, throwExceptionIfNotFound) {
	ClassFileParser parser1("res/com/test/SingleMethod.class");
	JavaClass javaClass1;
	parser1.parse(javaClass1);

	EXPECT_THROW(javaClass1.getMethod("hello", "()Ljava/lang/Number;"),
			MethodNotFoundException);
	EXPECT_THROW(javaClass1.getMethod("world", "()Ljava/lang/String;"),
			MethodNotFoundException);
}
