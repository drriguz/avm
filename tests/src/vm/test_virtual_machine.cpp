#include "gtest/gtest.h"

#include <iostream>

#include "vm/virtual_machine.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(VirtulMachine, throwExceptionIfClassNotFound) {
	VirtualMachine vm("res", "com.vm.HelloWorld");
	EXPECT_THROW(vm.execute(),
			ClassNotFoundException);
}
