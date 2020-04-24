#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"


#include <iostream>
#include <string>

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

void avm::invoke_getstatic       (Context& context, const Instruction* instruction) {
    VmField* theField = Interpreter::lookupField(context, instruction->getOprandAsU2());
    context.frame()->getOperandStack()->pushField(theField);
}

void avm::invoke_putstatic       (Context& context, const Instruction* instruction) {
    VmField* theField = Interpreter::lookupField(context, instruction->getOprandAsU2());
    context.frame()->getOperandStack()->popField(theField);
}
void avm::invoke_getfield        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_putfield        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_invokevirtual   (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprandAsU2();
    std::cout << "invoke_virtual #" << index << std::endl;
}
void avm::invoke_invokespecial   (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_invokestatic    (Context& context, const Instruction* instruction) {

    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_invokeinterface (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_invokedynamic   (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_new             (Context& context, const Instruction* instruction) {
    u2 index = instruction->getOprandAsU2();
    std::cout << "invoke_new #" << index << std::endl;

    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_newarray        (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_anewarray       (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_arraylength     (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_athrow          (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_checkcast       (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_instanceof      (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_monitorenter    (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}
void avm::invoke_monitorexit     (Context& context, const Instruction* instruction) {
    throw UnsupportedInstructionException(std::to_string(instruction->getOpcode()));
}