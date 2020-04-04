#include "gtest/gtest.h"

#include <iostream>
#include "class_file/format/constant/utf8.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(ConstantUtf8, copyConstructor) {
	ConstantUtf8 str(5, "hello");
	ASSERT_STREQ("hello", str.getValue().c_str());

	ConstantUtf8 str2 = str;
	ASSERT_EQ(5, str2.getLength());
	ASSERT_STREQ("hello", str2.getValue().c_str());
}

