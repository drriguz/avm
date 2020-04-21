#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/virtual_machine.h"
#include "vm/thread_context.h"
#include "gtest/gtest.h"

using namespace avm;

/*
References


178 (0xb2)    getstatic
179 (0xb3)    putstatic
180 (0xb4)    getfield
181 (0xb5)    putfield
182 (0xb6)    invokevirtual
183 (0xb7)    invokespecial
184 (0xb8)    invokestatic
185 (0xb9)    invokeinterface
186 (0xba)    invokedynamic
187 (0xbb)    new
188 (0xbc)    newarray
189 (0xbd)    anewarray
190 (0xbe)    arraylength
191 (0xbf)    athrow
192 (0xc0)    checkcast
193 (0xc1)    instanceof
194 (0xc2)    monitorenter
195 (0xc3)    monitorexit
*/

TEST(Interperter, getStatic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    Interpreter interpreter;
    VmStack stack;
    auto vmClass = vm.getClass("com/test/Fields");
    Context ctx(&stack, &vm, vmClass->getRuntimeConstantPool());

    //Instruction instruction();
    //interpreter.invoke(&ctx, )
}