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

// pop: discard the top value
void avm::invoke_pop             (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->popSlot();
}

// pop2: discard the top one or two values (category 2 computational type = 2 slots)
void avm::invoke_pop2            (Context& context, const Instruction* instruction) {
    context.frame()->getOperandStack()->popSlot();
    context.frame()->getOperandStack()->popSlot();
}

// dup: duplicate the top value
// ..., value => ..., value, value
void avm::invoke_dup             (Context& context, const Instruction* instruction) {
    SLOT value = context.frame()->getOperandStack()->peekSlot(0);
    context.frame()->getOperandStack()->pushSlot(value);
}

// dup_x1: duplicate top value and insert two values down
// ..., value2, value1 => ..., value1, value2, value1
void avm::invoke_dup_x1          (Context& context, const Instruction* instruction) {
    SLOT value1 = context.frame()->getOperandStack()->popSlot();
    SLOT value2 = context.frame()->getOperandStack()->popSlot();
    context.frame()->getOperandStack()->pushSlot(value1);
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
}

// dup_x2: duplicate top value and insert three values down
// ..., value3, value2, value1 => ..., value1, value3, value2, value1
void avm::invoke_dup_x2          (Context& context, const Instruction* instruction) {
    SLOT value1 = context.frame()->getOperandStack()->popSlot();
    SLOT value2 = context.frame()->getOperandStack()->popSlot();
    SLOT value3 = context.frame()->getOperandStack()->popSlot();
    context.frame()->getOperandStack()->pushSlot(value1);
    context.frame()->getOperandStack()->pushSlot(value3);
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
}

// dup2: duplicate the top one or two values
// For category 2 types (long/double): ..., value => ..., value, value (2 slots each)
// For category 1 types: ..., value2, value1 => ..., value2, value1, value2, value1
void avm::invoke_dup2            (Context& context, const Instruction* instruction) {
    SLOT value1 = context.frame()->getOperandStack()->peekSlot(0);
    SLOT value2 = context.frame()->getOperandStack()->peekSlot(1);
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
}

// dup2_x1: duplicate top two values and insert three values down
// ..., value3, value2, value1 => ..., value2, value1, value3, value2, value1
void avm::invoke_dup2_x1         (Context& context, const Instruction* instruction) {
    SLOT value1 = context.frame()->getOperandStack()->popSlot();
    SLOT value2 = context.frame()->getOperandStack()->popSlot();
    SLOT value3 = context.frame()->getOperandStack()->popSlot();
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
    context.frame()->getOperandStack()->pushSlot(value3);
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
}

// dup2_x2: duplicate top two values and insert four values down
// ..., value4, value3, value2, value1 => ..., value2, value1, value4, value3, value2, value1
void avm::invoke_dup2_x2         (Context& context, const Instruction* instruction) {
    SLOT value1 = context.frame()->getOperandStack()->popSlot();
    SLOT value2 = context.frame()->getOperandStack()->popSlot();
    SLOT value3 = context.frame()->getOperandStack()->popSlot();
    SLOT value4 = context.frame()->getOperandStack()->popSlot();
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
    context.frame()->getOperandStack()->pushSlot(value4);
    context.frame()->getOperandStack()->pushSlot(value3);
    context.frame()->getOperandStack()->pushSlot(value2);
    context.frame()->getOperandStack()->pushSlot(value1);
}

// swap: swap top two values
// ..., value2, value1 => ..., value1, value2
void avm::invoke_swap            (Context& context, const Instruction* instruction) {
    SLOT value1 = context.frame()->getOperandStack()->popSlot();
    SLOT value2 = context.frame()->getOperandStack()->popSlot();
    context.frame()->getOperandStack()->pushSlot(value1);
    context.frame()->getOperandStack()->pushSlot(value2);
}
