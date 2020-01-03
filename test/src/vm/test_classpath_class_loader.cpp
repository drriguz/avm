#include "gtest/gtest.h"

#include <iostream>
#include "vm/classpath_class_loader.h"

#include "exceptions.h"

using namespace avm;

TEST(ClasspathClassLoader, parseClass) {
	ClasspathClassLoader loader("res");
	try{
		JavaClass loaded = loader.loadClass("com.test.Simple");
	} catch (std::exception const & err) {
		FAIL() << err.what();
	}
}

TEST(ClasspathClassLoader, throwExceptionIfClassNotFound) {
	ClasspathClassLoader loader("res");
	EXPECT_THROW(JavaClass loaded = loader.loadClass("com.test.NotExist"), FileOpenFailedException);
}

