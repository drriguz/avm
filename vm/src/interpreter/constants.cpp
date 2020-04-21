#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

/*
Constants

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
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aconst_null     (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_iconst_m1       (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
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
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lconst_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fconst_0        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fconst_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fconst_2        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dconst_0        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dconst_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_bipush          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_sipush          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ldc             (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ldc_w           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ldc2_w          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}