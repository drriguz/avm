#include "gtest/gtest.h"

#include <iostream>

#include "class_file/parser/java_class_parser.h"
#include "class_file/parser/class_file_parser.h"
#include "vm/method_area.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(MethodArea, throwExceptionIfClassNotFound) {
	MethodArea methodArea;
	EXPECT_THROW(methodArea.getClass("com.riguz.Simple"),
			ClassNotFoundException);
}


TEST(MethodArea, getClassIfClassFound) {
	MethodArea methodArea;
	ClassFileParser parser("res/com/test/Simple.class");
	JavaClass* javaClass = new JavaClass();
	parser.parse(*javaClass);

	methodArea.putClass("com.riguz.Simple", javaClass);
	try{
		const JavaClass* actual = methodArea.getClass("com.riguz.Simple");

		ASSERT_EQ(0xCAFEBABE, actual->getMagic());
		ASSERT_EQ(52, actual->getMajorVersion());
		ASSERT_EQ(0, actual->getMinorVersion());
	}  catch (std::exception const & err) {
		FAIL() << err.what();
	}
}

TEST(MethodArea, throwExceptionIfClassExists) {
	MethodArea methodArea;
	ClassFileParser parser("res/com/test/Simple.class");
	JavaClass* javaClass = new JavaClass();
	parser.parse(*javaClass);

	methodArea.putClass("com.riguz.Simple", javaClass);
	EXPECT_THROW(methodArea.putClass("com.riguz.Simple", javaClass),
			ClassNotFoundException);
}
