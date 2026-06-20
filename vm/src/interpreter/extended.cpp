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
    // wide prefix modifies the following instruction to use 2-byte local variable indices
    // TODO: requires special handling in the execute loop or parser
    throw UnsupportedInstructionException("wide: not yet supported");
}
void avm::invoke_multianewarray  (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("multianewarray: arrays not yet supported");
}
void avm::invoke_ifnull          (Context& context, const Instruction* instruction) {
    reference ref = context.frame()->getOperandStack()->popReference();
    if(ref == 0) {
        int16_t offset = (int16_t)instruction->getOprandAsU2();
        int targetByteOffset = instruction->getByteOffset() + offset;
        int targetIdx = context.getMethod()->getInstructionIndexAtByteOffset(targetByteOffset);
        context.frame()->setPc(targetIdx);
    }
}
void avm::invoke_ifnonnull       (Context& context, const Instruction* instruction) {
    reference ref = context.frame()->getOperandStack()->popReference();
    if(ref != 0) {
        int16_t offset = (int16_t)instruction->getOprandAsU2();
        int targetByteOffset = instruction->getByteOffset() + offset;
        int targetIdx = context.getMethod()->getInstructionIndexAtByteOffset(targetByteOffset);
        context.frame()->setPc(targetIdx);
    }
}
void avm::invoke_goto_w          (Context& context, const Instruction* instruction) {
    // goto_w has a 4-byte offset, but the Instruction class only supports 2-byte operands
    // TODO: requires parser support for 4-byte operands
    throw UnsupportedInstructionException("goto_w: not yet supported (4-byte offset)");
}
void avm::invoke_jsr_w           (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException("jsr_w: not yet supported");
}
