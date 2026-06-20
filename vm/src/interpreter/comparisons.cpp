#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace avm;

/*
Comparisons

148 (0x94)    lcmp
149 (0x95)    fcmpl
150 (0x96)    fcmpg
151 (0x97)    dcmpl
152 (0x98)    dcmpg
153 (0x99)    ifeq
154 (0x9a)    ifne
155 (0x9b)    iflt
156 (0x9c)    ifge
157 (0x9d)    ifgt
158 (0x9e)    ifle
159 (0x9f)    if_icmpeq
160 (0xa0)    if_icmpne
161 (0xa1)    if_icmplt
162 (0xa2)    if_icmpge
163 (0xa3)    if_icmpgt
164 (0xa4)    if_icmple
165 (0xa5)    if_acmpeq
166 (0xa6)    if_acmpne
*/

// Helper: calculate branch target for conditional branch instructions.
// The branch offset in the bytecode is relative to the branch instruction's byte offset.
// We compute the target byte offset, then find the instruction index for it.
static inline void branch(Context& context, const Instruction* instruction, bool condition) {
    if(condition) {
        int16_t offset = (int16_t)instruction->getOprandAsU2();
        int targetByteOffset = instruction->getByteOffset() + offset;
        int targetIdx = context.getMethod()->getInstructionIndexAtByteOffset(targetByteOffset);
        // getNextPc() returns current PC and increments, so setting PC to targetIdx
        // means getNextPc() returns targetIdx (fetching the right instruction) and increments to targetIdx+1
        context.frame()->setPc(targetIdx);
    }
}

void avm::invoke_lcmp            (Context& context, const Instruction* instruction) {
    int64_t i1 = context.frame()->getOperandStack()->popLong();
    int64_t i2 = context.frame()->getOperandStack()->popLong();
    if(i2 > i1) context.frame()->getOperandStack()->pushInt(1);
    else if(i2 == i1) context.frame()->getOperandStack()->pushInt(0);
    else context.frame()->getOperandStack()->pushInt(-1);
}
void avm::invoke_fcmpl           (Context& context, const Instruction* instruction) {
    float i1 = context.frame()->getOperandStack()->popFloat();
    float i2 = context.frame()->getOperandStack()->popFloat();
    if(std::isnan(i1) || std::isnan(i2)) {
        context.frame()->getOperandStack()->pushInt(-1);
    } else if(i2 > i1) {
        context.frame()->getOperandStack()->pushInt(1);
    } else if(i2 == i1) {
        context.frame()->getOperandStack()->pushInt(0);
    } else {
        context.frame()->getOperandStack()->pushInt(-1);
    }
}
void avm::invoke_fcmpg           (Context& context, const Instruction* instruction) {
    float i1 = context.frame()->getOperandStack()->popFloat();
    float i2 = context.frame()->getOperandStack()->popFloat();
    if(std::isnan(i1) || std::isnan(i2)) {
        context.frame()->getOperandStack()->pushInt(1);
    } else if(i2 > i1) {
        context.frame()->getOperandStack()->pushInt(1);
    } else if(i2 == i1) {
        context.frame()->getOperandStack()->pushInt(0);
    } else {
        context.frame()->getOperandStack()->pushInt(-1);
    }
}
void avm::invoke_dcmpl           (Context& context, const Instruction* instruction) {
    double i1 = context.frame()->getOperandStack()->popDouble();
    double i2 = context.frame()->getOperandStack()->popDouble();
    if(std::isnan(i1) || std::isnan(i2)) {
        context.frame()->getOperandStack()->pushInt(-1);
    } else if(i2 > i1) {
        context.frame()->getOperandStack()->pushInt(1);
    } else if(i2 == i1) {
        context.frame()->getOperandStack()->pushInt(0);
    } else {
        context.frame()->getOperandStack()->pushInt(-1);
    }
}
void avm::invoke_dcmpg           (Context& context, const Instruction* instruction) {
    double i1 = context.frame()->getOperandStack()->popDouble();
    double i2 = context.frame()->getOperandStack()->popDouble();
    if(std::isnan(i1) || std::isnan(i2)) {
        context.frame()->getOperandStack()->pushInt(1);
    } else if(i2 > i1) {
        context.frame()->getOperandStack()->pushInt(1);
    } else if(i2 == i1) {
        context.frame()->getOperandStack()->pushInt(0);
    } else {
        context.frame()->getOperandStack()->pushInt(-1);
    }
}
// Single-operand conditional branches
void avm::invoke_ifeq            (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, value == 0);
}
void avm::invoke_ifne            (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, value != 0);
}
void avm::invoke_iflt            (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, value < 0);
}
void avm::invoke_ifge            (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, value >= 0);
}
void avm::invoke_ifgt            (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, value > 0);
}
void avm::invoke_ifle            (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, value <= 0);
}
// Two-operand integer conditional branches
void avm::invoke_if_icmpeq       (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, i2 == i1);
}
void avm::invoke_if_icmpne       (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, i2 != i1);
}
void avm::invoke_if_icmplt       (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, i2 < i1);
}
void avm::invoke_if_icmpge       (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, i2 >= i1);
}
void avm::invoke_if_icmpgt       (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, i2 > i1);
}
void avm::invoke_if_icmple       (Context& context, const Instruction* instruction) {
    int32_t i1 = context.frame()->getOperandStack()->popInt();
    int32_t i2 = context.frame()->getOperandStack()->popInt();
    branch(context, instruction, i2 <= i1);
}
// Reference conditional branches
void avm::invoke_if_acmpeq       (Context& context, const Instruction* instruction) {
    reference i1 = context.frame()->getOperandStack()->popReference();
    reference i2 = context.frame()->getOperandStack()->popReference();
    branch(context, instruction, i2 == i1);
}
void avm::invoke_if_acmpne       (Context& context, const Instruction* instruction) {
    reference i1 = context.frame()->getOperandStack()->popReference();
    reference i2 = context.frame()->getOperandStack()->popReference();
    branch(context, instruction, i2 != i1);
}
