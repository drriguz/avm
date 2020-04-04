#include "gtest/gtest.h"

#include <iostream>
#include "class_file/helper/strings.h"

#include "class_file/exceptions.h"

using namespace avm;

TEST(Strings, replaceAll) {
	ASSERT_STREQ("com/riguz/Simple", Strings::replaceAll("com.riguz.Simple", ".", "/").c_str());
	ASSERT_STREQ("com.riguz.Simple", Strings::replaceAll("com.riguz.Simple", "$$", "/").c_str());
	ASSERT_STREQ("com##riguz##Simple", Strings::replaceAll("com.riguz.Simple", ".", "##").c_str());
	ASSERT_STREQ("*********", Strings::replaceAll("abcabcabc", "abc", "***").c_str());
}

