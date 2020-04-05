#include "gtest/gtest.h"

#include "vm/runtime/local_variables.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(LocalVariables, saveAndGetSingleByteValues) {
	LocalVariables var(5);
	var.setByte(0, 18);
	ASSERT_EQ(18, var.getByte(0));
}

TEST(LocalVariables, saveAndGetDoubleByteValues) {
	
}

TEST(LocalVariables, saveAndGetNegativeByteValues) {
	
}


TEST(LocalVariables, throwExceptionIfOutOfRange) {
	
}