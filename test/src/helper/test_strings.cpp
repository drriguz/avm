#include "gtest/gtest.h"

#include <iostream>
#include "helper/strings.h"

#include "exceptions.h"

using namespace avm;

TEST(Strings, replaceAll) {
	ASSERT_STREQ("com/riguz/Simple", Strings::replaceAll("com.riguz.Simple", ".", "/").c_str());
	ASSERT_STREQ("com.riguz.Simple", Strings::replaceAll("com.riguz.Simple", "$$", "/").c_str());
	ASSERT_STREQ("com##riguz##Simple", Strings::replaceAll("com.riguz.Simple", ".", "##").c_str());
	ASSERT_STREQ("*********", Strings::replaceAll("abcabcabc", "abc", "***").c_str());
}

