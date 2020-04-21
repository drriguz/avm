#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/virtual_machine.h"
#include "vm/thread_context.h"
#include "gtest/gtest.h"

using namespace avm;

TEST(Interperter, getStatic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    Interpreter interpreter;
    auto vmClass = vm.getClass("com/op/FieldOperations");
    Frame frame(3, 3, vmClass->getRuntimeConstantPool());

    Context ctx(&frame, &vm);
    vmClass->getField("count")->setInt(1024);
    Instruction getCount(j_getstatic, 0, 2);
    interpreter.invoke(&ctx, &getCount);

    ASSERT_EQ(1, frame.getOperandStack()->size());
    ASSERT_EQ(1024, frame.getOperandStack()->popInt());
}