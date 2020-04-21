#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

/*
Stack

87 (0x57)    pop
88 (0x58)    pop2
89 (0x59)    dup
90 (0x5a)    dup_x1
91 (0x5b)    dup_x2
92 (0x5c)    dup2
93 (0x5d)    dup2_x1
94 (0x5e)    dup2_x2
95 (0x5f)    swap
*/

void avm::invoke_pop             (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_pop2            (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dup             (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dup_x1          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dup_x2          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dup2            (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dup2_x1         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dup2_x2         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_swap            (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}