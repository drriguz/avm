#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

/*
Loads

21 (0x15)    iload
22 (0x16)    lload
23 (0x17)    fload
24 (0x18)    dload
25 (0x19)    aload
26 (0x1a)    iload_0
27 (0x1b)    iload_1
28 (0x1c)    iload_2
29 (0x1d)    iload_3
30 (0x1e)    lload_0
31 (0x1f)    lload_1
32 (0x20)    lload_2
33 (0x21)    lload_3
34 (0x22)    fload_0
35 (0x23)    fload_1
36 (0x24)    fload_2
37 (0x25)    fload_3
38 (0x26)    dload_0
39 (0x27)    dload_1
40 (0x28)    dload_2
41 (0x29)    dload_3
42 (0x2a)    aload_0
43 (0x2b)    aload_1
44 (0x2c)    aload_2
45 (0x2d)    aload_3
46 (0x2e)    iaload
47 (0x2f)    laload
48 (0x30)    faload
49 (0x31)    daload
50 (0x32)    aaload
51 (0x33)    baload
52 (0x34)    caload
53 (0x35)    saload
*/

void avm::invoke_iload           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lload           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fload           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dload           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aload           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_iload_0         (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(0));
}
void avm::invoke_iload_1         (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(1));
}
void avm::invoke_iload_2         (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(2));
}
void avm::invoke_iload_3         (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->pushInt(context.frame()->getLocalVariables()->getInt(3));
}
void avm::invoke_lload_0         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lload_1         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lload_2         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lload_3         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fload_0         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fload_1         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fload_2         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fload_3         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dload_0         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dload_1         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dload_2         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dload_3         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aload_0         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aload_1         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aload_2         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aload_3         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_iaload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_laload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_faload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_daload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aaload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_baload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_caload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_saload          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}