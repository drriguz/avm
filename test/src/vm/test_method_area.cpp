#include "gtest/gtest.h"

#include <iostream>

#include "parser/java_class_parser.h"
#include "parser/class_file_parser.h"
#include "vm/method_area.h"

#include "exceptions.h"

using namespace avm;

TEST(MethodArea, throwExceptionIfClassNotFound) {
	MethodArea methodArea;
	EXPECT_THROW(methodArea.getClass("com.riguz.Simple"),
			ClassNotFoundException);
}

TEST(MethodArea, getClassIfClassFound) {
	MethodArea methodArea;
	ClassFileParser parser("res/com/test/Simple.class");
	const JavaClass javaClass = parser.parse();

	methodArea.putClass("com.riguz.Simple", javaClass);
	try{
		methodArea.getClass("com.riguz.Simple");
		JavaClass actual = methodArea.getClass("com.riguz.Simple");

		ASSERT_EQ(0xCAFEBABE, javaClass.getMagic());
		ASSERT_EQ(52, javaClass.getMajorVersion());
		ASSERT_EQ(0, javaClass.getMinorVersion());
	}  catch (std::exception const & err) {
		FAIL() << err.what();
	}
}
