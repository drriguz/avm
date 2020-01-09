#include "gtest/gtest.h"

#include <iostream>
#include "format/constant/utf8.h"
#include "format/constant/constant_info.h"

#include "exceptions.h"

using namespace avm;


TEST(ConstantInfo, constructor) {
	ConstantInfo info;

	ASSERT_EQ(0, info.getSize());
	ASSERT_EQ(nullptr, info.getInfo());
}

TEST(ConstantInfo, copyConstructor) {
	ConstantInfo info1;
	ConstantInfo info = info1;
	ASSERT_EQ(0, info.getSize());
	ASSERT_EQ(nullptr, info.getInfo());

	// ConstantInfo info2(ConstantType::Utf8, "hello", 5);

}


