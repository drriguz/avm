#include "gtest/gtest.h"

#include <iostream>

#include "vm/virtual_machine.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(VirtulMachine, execute) {
	VirtualMachine vm("res", "com.vm.HelloWorld");
	vm.execute();
}

TEST(VirtulMachine, throwExceptionIfClassNotFound) {
	VirtualMachine vm("res", "com.vm.NotHere");
	EXPECT_THROW(vm.execute(),
			ClassNotFoundException);
}
