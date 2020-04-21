#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

/*
Extended

196 (0xc4)    wide
197 (0xc5)    multianewarray
198 (0xc6)    ifnull
199 (0xc7)    ifnonnull
200 (0xc8)    goto_w
201 (0xc9)    jsr_w
*/

void avm::invoke_wide            (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_multianewarray  (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ifnull          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ifnonnull       (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_goto_w          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_jsr_w           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}