#include "vm/interpreter.h"
#include "vm/exceptions.h"
#include "vm/thread_context.h"
#include "class_file/format/constant_pool.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace avm;

/*
Conversions

133 (0x85)    i2l
134 (0x86)    i2f
135 (0x87)    i2d
136 (0x88)    l2i
137 (0x89)    l2f
138 (0x8a)    l2d
139 (0x8b)    f2i
140 (0x8c)    f2l
141 (0x8d)    f2d
142 (0x8e)    d2i
143 (0x8f)    d2l
144 (0x90)    d2f
145 (0x91)    i2b
146 (0x92)    i2c
147 (0x93)    i2s
*/

void avm::invoke_i2l             (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushLong((int64_t)value);
}
void avm::invoke_i2f             (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushFloat((float)value);
}
void avm::invoke_i2d             (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushDouble((double)value);
}
void avm::invoke_l2i             (Context& context, const Instruction* instruction) {
    int64_t value = context.frame()->getOperandStack()->popLong();
    context.frame()->getOperandStack()->pushInt((int32_t)value);
}
void avm::invoke_l2f             (Context& context, const Instruction* instruction) {
    int64_t value = context.frame()->getOperandStack()->popLong();
    context.frame()->getOperandStack()->pushFloat((float)value);
}
void avm::invoke_l2d             (Context& context, const Instruction* instruction) {
    int64_t value = context.frame()->getOperandStack()->popLong();
    context.frame()->getOperandStack()->pushDouble((double)value);
}
void avm::invoke_f2i             (Context& context, const Instruction* instruction) {
    float value = context.frame()->getOperandStack()->popFloat();
    if(std::isnan(value)) {
        context.frame()->getOperandStack()->pushInt(0);
    } else if(value >= (float)INT32_MAX) {
        context.frame()->getOperandStack()->pushInt(INT32_MAX);
    } else if(value <= (float)INT32_MIN) {
        context.frame()->getOperandStack()->pushInt(INT32_MIN);
    } else {
        context.frame()->getOperandStack()->pushInt((int32_t)value);
    }
}
void avm::invoke_f2l             (Context& context, const Instruction* instruction) {
    float value = context.frame()->getOperandStack()->popFloat();
    if(std::isnan(value)) {
        context.frame()->getOperandStack()->pushLong(0);
    } else if(value >= (float)INT64_MAX) {
        context.frame()->getOperandStack()->pushLong(INT64_MAX);
    } else if(value <= (float)INT64_MIN) {
        context.frame()->getOperandStack()->pushLong(INT64_MIN);
    } else {
        context.frame()->getOperandStack()->pushLong((int64_t)value);
    }
}
void avm::invoke_f2d             (Context& context, const Instruction* instruction) {
    float value = context.frame()->getOperandStack()->popFloat();
    context.frame()->getOperandStack()->pushDouble((double)value);
}
void avm::invoke_d2i             (Context& context, const Instruction* instruction) {
    double value = context.frame()->getOperandStack()->popDouble();
    if(std::isnan(value)) {
        context.frame()->getOperandStack()->pushInt(0);
    } else if(value >= (double)INT32_MAX) {
        context.frame()->getOperandStack()->pushInt(INT32_MAX);
    } else if(value <= (double)INT32_MIN) {
        context.frame()->getOperandStack()->pushInt(INT32_MIN);
    } else {
        context.frame()->getOperandStack()->pushInt((int32_t)value);
    }
}
void avm::invoke_d2l             (Context& context, const Instruction* instruction) {
    double value = context.frame()->getOperandStack()->popDouble();
    if(std::isnan(value)) {
        context.frame()->getOperandStack()->pushLong(0);
    } else if(value >= (double)INT64_MAX) {
        context.frame()->getOperandStack()->pushLong(INT64_MAX);
    } else if(value <= (double)INT64_MIN) {
        context.frame()->getOperandStack()->pushLong(INT64_MIN);
    } else {
        context.frame()->getOperandStack()->pushLong((int64_t)value);
    }
}
void avm::invoke_d2f             (Context& context, const Instruction* instruction) {
    double value = context.frame()->getOperandStack()->popDouble();
    context.frame()->getOperandStack()->pushFloat((float)value);
}
void avm::invoke_i2b             (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushInt((int32_t)(int8_t)value);
}
void avm::invoke_i2c             (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushInt((int32_t)(uint16_t)value);
}
void avm::invoke_i2s             (Context& context, const Instruction* instruction) {
    int32_t value = context.frame()->getOperandStack()->popInt();
    context.frame()->getOperandStack()->pushInt((int32_t)(int16_t)value);
}
