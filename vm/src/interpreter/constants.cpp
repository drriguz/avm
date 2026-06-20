#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"

#include <iostream>
#include <string>

using namespace avm;

/*
Constants: constants => Oprand stack

00 (0x00)    nop
01 (0x01)    aconst_null
02 (0x02)    iconst_m1
03 (0x03)    iconst_0
04 (0x04)    iconst_1
05 (0x05)    iconst_2
06 (0x06)    iconst_3
07 (0x07)    iconst_4
08 (0x08)    iconst_5
09 (0x09)    lconst_0
10 (0x0a)    lconst_1
11 (0x0b)    fconst_0
12 (0x0c)    fconst_1
13 (0x0d)    fconst_2
14 (0x0e)    dconst_0
15 (0x0f)    dconst_1
16 (0x10)    bipush
17 (0x11)    sipush
18 (0x12)    ldc
19 (0x13)    ldc_w
20 (0x14)    ldc2_w
*/

void avm::invoke_nop             (Context& context, const Instruction* instruction) {
    // do nothing
}
void avm::invoke_aconst_null     (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushReference(0);
}
void avm::invoke_iconst_m1       (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(-1);
}
void avm::invoke_iconst_0        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(0);
}
void avm::invoke_iconst_1        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(1);
}
void avm::invoke_iconst_2        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(2);
}
void avm::invoke_iconst_3        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(3);
}
void avm::invoke_iconst_4        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(4);
}
void avm::invoke_iconst_5        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(5);
}
void avm::invoke_lconst_0        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushLong(0);
}
void avm::invoke_lconst_1        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushLong(1);
}
void avm::invoke_fconst_0        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushFloat(0.0f);
}
void avm::invoke_fconst_1        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushFloat(1.0f);
}
void avm::invoke_fconst_2        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushFloat(2.0f);
}
void avm::invoke_dconst_0        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushDouble(0.0);
}
void avm::invoke_dconst_1        (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushDouble(1.0);
}
void avm::invoke_bipush          (Context& context, const Instruction* instruction) {
    int8_t value = (int8_t)instruction->getOprand(0);
    context.frame()->getOperandStack()->pushInt((int32_t)value);
}
void avm::invoke_sipush          (Context& context, const Instruction* instruction) {
    int16_t value = (int16_t)instruction->getOprandAsU2();
    context.frame()->getOperandStack()->pushInt((int32_t)value);
}
void avm::invoke_ldc             (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprand(0);
    const ConstantPool* cp = context.frame()->getRuntimeConstantPool();
    const ConstantInfo* info = cp->at(index);
    switch(info->getType()) {
    case CONSTANT_Integer: {
        int32_t value = (int32_t)((const ConstantInteger*)info)->getValue();
        context.frame()->getOperandStack()->pushInt(value);
        break;
    }
    case CONSTANT_Float: {
        float value = ((const ConstantFloat*)info)->getValue();
        context.frame()->getOperandStack()->pushFloat(value);
        break;
    }
    case CONSTANT_String: {
        u2 stringIndex = ((const ConstantString*)info)->getStringIndex();
        const std::string* strRef = cp->getStringReference(stringIndex);
        context.frame()->getOperandStack()->pushReference(reinterpret_cast<int64_t>(strRef));
        break;
    }
    default:
        throw UnsupportedInstructionException("ldc: unsupported constant type");
    }
}
void avm::invoke_ldc_w           (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprandAsU2();
    const ConstantPool* cp = context.frame()->getRuntimeConstantPool();
    const ConstantInfo* info = cp->at(index);
    switch(info->getType()) {
    case CONSTANT_Integer: {
        int32_t value = (int32_t)((const ConstantInteger*)info)->getValue();
        context.frame()->getOperandStack()->pushInt(value);
        break;
    }
    case CONSTANT_Float: {
        float value = ((const ConstantFloat*)info)->getValue();
        context.frame()->getOperandStack()->pushFloat(value);
        break;
    }
    case CONSTANT_String: {
        u2 stringIndex = ((const ConstantString*)info)->getStringIndex();
        const std::string* strRef = cp->getStringReference(stringIndex);
        context.frame()->getOperandStack()->pushReference(reinterpret_cast<int64_t>(strRef));
        break;
    }
    default:
        throw UnsupportedInstructionException("ldc_w: unsupported constant type");
    }
}
void avm::invoke_ldc2_w          (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprandAsU2();
    const ConstantPool* cp = context.frame()->getRuntimeConstantPool();
    const ConstantInfo* info = cp->at(index);
    switch(info->getType()) {
    case CONSTANT_Long: {
        int64_t value = (int64_t)((const ConstantLong*)info)->getValue();
        context.frame()->getOperandStack()->pushLong(value);
        break;
    }
    case CONSTANT_Double: {
        double value = ((const ConstantDouble*)info)->getValue();
        context.frame()->getOperandStack()->pushDouble(value);
        break;
    }
    default:
        throw UnsupportedInstructionException("ldc2_w: unsupported constant type");
    }
}
