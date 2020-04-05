#include "gtest/gtest.h"

#include "vm/runtime/operand_stack.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(OperandStack, pushAndPopSingleByteValues) {
	OperandStack stack(4);
	stack.pushByte(-18);
	stack.pushByte(18);
	stack.pushShort(19);
	stack.pushInt(20);
	ASSERT_EQ(20, stack.popInt());
	ASSERT_EQ(19, stack.popShort());
	ASSERT_EQ(18, stack.popByte());
	ASSERT_EQ(-18, stack.popByte());
}

TEST(OperandStack, pushAndPopLong) {
	OperandStack stack(4);
	stack.pushLong(12345678);
	ASSERT_EQ(12345678, stack.popLong());
}

TEST(OperandStack, pushAndPopSignedLong) {
	OperandStack stack(4);
	stack.pushLong(-12345678);
	ASSERT_EQ(-12345678, stack.popLong());
}

TEST(OperandStack, pushAndPopDouble) {
	OperandStack stack(2);
	stack.pushDouble(12345.6789);
	ASSERT_EQ(12345.6789, stack.popDouble());
}

TEST(OperandStack, throwExceptionIfExceedLimit) {
	OperandStack stack(1);
	stack.pushByte(18);
	EXPECT_THROW(stack.pushByte(18),
			StackOutOfRangeException);
}