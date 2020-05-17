#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

/*
Stores: Oprand stack => Local Variables

54 (0x36)    istore
55 (0x37)    lstore
56 (0x38)    fstore
57 (0x39)    dstore
58 (0x3a)    astore
59 (0x3b)    istore_0
60 (0x3c)    istore_1
61 (0x3d)    istore_2
62 (0x3e)    istore_3
63 (0x3f)    lstore_0
64 (0x40)    lstore_1
65 (0x41)    lstore_2
66 (0x42)    lstore_3
67 (0x43)    fstore_0
68 (0x44)    fstore_1
69 (0x45)    fstore_2
70 (0x46)    fstore_3
71 (0x47)    dstore_0
72 (0x48)    dstore_1
73 (0x49)    dstore_2
74 (0x4a)    dstore_3
75 (0x4b)    astore_0
76 (0x4c)    astore_1
77 (0x4d)    astore_2
78 (0x4e)    astore_3
79 (0x4f)    iastore
80 (0x50)    lastore
81 (0x51)    fastore
82 (0x52)    dastore
83 (0x53)    aastore
84 (0x54)    bastore
85 (0x55)    castore
86 (0x56)    sastore
*/


void avm::invoke_istore          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lstore          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fstore          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dstore          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_astore          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_istore_0        (Context& context, const Instruction* instruction) {
    context.frame()->getLocalVariables()->setInt(0, context.frame()->getOperandStack()->popInt());
}
void avm::invoke_istore_1        (Context& context, const Instruction* instruction) {
    context.frame()->getLocalVariables()->setInt(1, context.frame()->getOperandStack()->popInt());
}
void avm::invoke_istore_2        (Context& context, const Instruction* instruction) {
    context.frame()->getLocalVariables()->setInt(2, context.frame()->getOperandStack()->popInt());
}
void avm::invoke_istore_3        (Context& context, const Instruction* instruction) {
    context.frame()->getLocalVariables()->setInt(3, context.frame()->getOperandStack()->popInt());
}
void avm::invoke_lstore_0        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lstore_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lstore_2        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lstore_3        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fstore_0        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fstore_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fstore_2        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fstore_3        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dstore_0        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dstore_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dstore_2        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dstore_3        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_astore_0        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_astore_1        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_astore_2        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_astore_3        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_iastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_fastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_aastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_bastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_castore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_sastore         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}