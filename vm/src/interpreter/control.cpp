#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

using namespace avm;

/*
Control

167 (0xa7)    goto
168 (0xa8)    jsr
169 (0xa9)    ret
170 (0xaa)    tableswitch
171 (0xab)    lookupswitch
172 (0xac)    ireturn
173 (0xad)    lreturn
174 (0xae)    freturn
175 (0xaf)    dreturn
176 (0xb0)    areturn
177 (0xb1)    return
*/

void avm::invoke_goto            (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_jsr             (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ret             (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_tableswitch     (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_lookupswitch    (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_ireturn         (Context& context, const Instruction* instruction) {
    int32_t returnValue = context.frame()->getOperandStack()->popInt();
    context.previousFrame()->getOperandStack()->pushInt(returnValue);
    context.getStack()->pop();
}
void avm::invoke_lreturn         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_freturn         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_dreturn         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_areturn         (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_return          (Context& context, const Instruction* instruction) {
    // do nothing
}