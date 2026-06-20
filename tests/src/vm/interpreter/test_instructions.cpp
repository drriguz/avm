#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/virtual_machine.h"
#include "vm/thread_context.h"
#include "gtest/gtest.h"

using namespace avm;

// ============================================================
// Constants
// ============================================================

TEST(Instructions, iconst_m1) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 2, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_iconst_m1);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(-1, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, aconst_null) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 2, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_aconst_null);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ((reference)0, stack.currentFrame()->getOperandStack()->popReference());
}

TEST(Instructions, bipush) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 2, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_bipush, 100);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(100, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, bipush_negative) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 2, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    // -56 as unsigned byte = 200
    Instruction inst(j_bipush, 200);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(-56, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, sipush) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 2, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    // 300 = 0x012C -> high=0x01, low=0x2C
    Instruction inst(j_sipush, 0x01, 0x2C);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(300, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, lconst_0) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_lconst_0);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(0L, stack.currentFrame()->getOperandStack()->popLong());
}

TEST(Instructions, lconst_1) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_lconst_1);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(1L, stack.currentFrame()->getOperandStack()->popLong());
}

TEST(Instructions, fconst_0) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_fconst_0);
    interp.invoke(&ctx, &inst);
    ASSERT_FLOAT_EQ(0.0f, stack.currentFrame()->getOperandStack()->popFloat());
}

TEST(Instructions, fconst_1) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_fconst_1);
    interp.invoke(&ctx, &inst);
    ASSERT_FLOAT_EQ(1.0f, stack.currentFrame()->getOperandStack()->popFloat());
}

TEST(Instructions, fconst_2) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_fconst_2);
    interp.invoke(&ctx, &inst);
    ASSERT_FLOAT_EQ(2.0f, stack.currentFrame()->getOperandStack()->popFloat());
}

TEST(Instructions, dconst_0) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_dconst_0);
    interp.invoke(&ctx, &inst);
    ASSERT_DOUBLE_EQ(0.0, stack.currentFrame()->getOperandStack()->popDouble());
}

TEST(Instructions, dconst_1) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    Instruction inst(j_dconst_1);
    interp.invoke(&ctx, &inst);
    ASSERT_DOUBLE_EQ(1.0, stack.currentFrame()->getOperandStack()->popDouble());
}

// ============================================================
// Loads (generic indexed)
// ============================================================

TEST(Instructions, iload) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getLocalVariables()->setInt(2, 42);
    Instruction inst(j_iload, 2);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(42, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, aload_generic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getLocalVariables()->setReference(1, 0x1234);
    Instruction inst(j_aload, 1);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ((reference)0x1234, stack.currentFrame()->getOperandStack()->popReference());
}

// ============================================================
// Stores (generic indexed)
// ============================================================

TEST(Instructions, istore) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(99);
    Instruction inst(j_istore, 3);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(99, stack.currentFrame()->getLocalVariables()->getInt(3));
}

TEST(Instructions, astore) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushReference(0xABCD);
    Instruction inst(j_astore, 2);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ((reference)0xABCD, stack.currentFrame()->getLocalVariables()->getReference(2));
}

// ============================================================
// Stack Operations
// ============================================================

TEST(Instructions, pop) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(1);
    stack.currentFrame()->getOperandStack()->pushInt(2);
    Instruction inst(j_pop);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(1, stack.currentFrame()->getOperandStack()->size());
    ASSERT_EQ(1, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, dup) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(42);
    Instruction inst(j_dup);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(2, stack.currentFrame()->getOperandStack()->size());
    ASSERT_EQ(42, stack.currentFrame()->getOperandStack()->popInt());
    ASSERT_EQ(42, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, swap) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ConstantOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(1);
    stack.currentFrame()->getOperandStack()->pushInt(2);
    Instruction inst(j_swap);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(1, stack.currentFrame()->getOperandStack()->popInt());
    ASSERT_EQ(2, stack.currentFrame()->getOperandStack()->popInt());
}

// ============================================================
// Integer Math
// ============================================================

TEST(Instructions, iadd_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(10);
    stack.currentFrame()->getOperandStack()->pushInt(20);
    Instruction inst(j_iadd);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(30, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, isub_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(10);
    stack.currentFrame()->getOperandStack()->pushInt(3);
    Instruction inst(j_isub);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(7, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, imul_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(6);
    stack.currentFrame()->getOperandStack()->pushInt(7);
    Instruction inst(j_imul);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(42, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, idiv_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(20);
    stack.currentFrame()->getOperandStack()->pushInt(4);
    Instruction inst(j_idiv);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(5, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, idiv_by_zero) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(10);
    stack.currentFrame()->getOperandStack()->pushInt(0);
    Instruction inst(j_idiv);
    ASSERT_THROW(interp.invoke(&ctx, &inst), RuntimeException);
}

TEST(Instructions, irem_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(17);
    stack.currentFrame()->getOperandStack()->pushInt(5);
    Instruction inst(j_irem);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(2, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, ineg_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(42);
    Instruction inst(j_ineg);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(-42, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, iand_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(0xFF);
    stack.currentFrame()->getOperandStack()->pushInt(0x0F);
    Instruction inst(j_iand);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(0x0F, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, ior_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(0xF0);
    stack.currentFrame()->getOperandStack()->pushInt(0x0F);
    Instruction inst(j_ior);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(0xFF, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, ixor_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(0xFF);
    stack.currentFrame()->getOperandStack()->pushInt(0x0F);
    Instruction inst(j_ixor);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(0xF0, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, ishl_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(1);
    stack.currentFrame()->getOperandStack()->pushInt(4);
    Instruction inst(j_ishl);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(16, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, ishr_basic) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/MathOperations");
    auto frame = std::unique_ptr<Frame>(new Frame(2, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushInt(32);
    stack.currentFrame()->getOperandStack()->pushInt(3);
    Instruction inst(j_ishr);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(4, stack.currentFrame()->getOperandStack()->popInt());
}

// ============================================================
// Comparisons
// ============================================================

TEST(Instructions, lcmp_equal) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ControlFlow");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushLong(100L);
    stack.currentFrame()->getOperandStack()->pushLong(100L);
    Instruction inst(j_lcmp);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(0, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, lcmp_greater) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ControlFlow");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushLong(200L);
    stack.currentFrame()->getOperandStack()->pushLong(100L);
    Instruction inst(j_lcmp);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(1, stack.currentFrame()->getOperandStack()->popInt());
}

TEST(Instructions, lcmp_less) {
    VirtualMachine vm("res", "com/vm/HelloWorld");
    VmStack stack;
    auto vmClass = vm.getClass("com/op/ControlFlow");
    auto frame = std::unique_ptr<Frame>(new Frame(4, 4, vmClass->getRuntimeConstantPool(), nullptr));
    stack.push(std::move(frame));
    Context ctx(&vm, &stack);
    Interpreter interp;

    stack.currentFrame()->getOperandStack()->pushLong(50L);
    stack.currentFrame()->getOperandStack()->pushLong(100L);
    Instruction inst(j_lcmp);
    interp.invoke(&ctx, &inst);
    ASSERT_EQ(-1, stack.currentFrame()->getOperandStack()->popInt());
}

// ============================================================
// Full Execution Tests (run Java methods end-to-end)
// ============================================================

TEST(Execution, constantOperations) {
    VirtualMachine vm("res", "com/op/ConstantOperations");
    try {
        vm.execute();
    } catch(const RuntimeException& e) {
        FAIL() << "Exception: " << e.what();
    }
}

TEST(Execution, mathOperations) {
    VirtualMachine vm("res", "com/op/MathOperations");
    try {
        vm.execute();
    } catch(const RuntimeException& e) {
        FAIL() << "Exception: " << e.what();
    }
}

TEST(Execution, controlFlow) {
    VirtualMachine vm("res", "com/op/ControlFlow");
    try {
        vm.execute();
    } catch(const RuntimeException& e) {
        FAIL() << "Exception: " << e.what();
    }
}

TEST(Execution, objectOperations) {
    VirtualMachine vm("res", "com/op/ObjectOperations");
    try {
        vm.execute();
    } catch(const RuntimeException& e) {
        FAIL() << "Exception: " << e.what();
    }
}
