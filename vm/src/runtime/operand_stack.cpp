#include "vm/runtime/operand_stack.h"
#include "vm/exceptions.h"
#include "vm/util/numbers.h"

using namespace avm;

OperandStack::OperandStack(int maxSize) :
        _maxSize(maxSize) {

}

OperandStack::~OperandStack() {

}

void OperandStack::checkStackSize(int valueSize) {
    int newSize = _variables.size() + valueSize;
    if (newSize > _maxSize)
        throw StackOutOfRangeException("Exceed max slot stack size");
}

void OperandStack::pushSingleByte(int32_t value) {
    checkStackSize(1);
    uint32_t *uv = reinterpret_cast<uint32_t*>(&value);
    Slot slot = Slot(*uv);
    _variables.push(slot);
}

void OperandStack::pushDoubleByte(int64_t value) {
    checkStackSize(2);
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
    _variables.push(Slot(highBytes));
    _variables.push(Slot(lowBytes));
}

int32_t OperandStack::popSingleByte() {
    Slot top = _variables.top();
    _variables.pop();
    return top.asInt();
}

int64_t OperandStack::popDoubleByte() {
    uint32_t lowBytes = _variables.top().getValue();
    _variables.pop();
    uint32_t highBytes = _variables.top().getValue();
    _variables.pop();
    return Numbers::asLong(highBytes, lowBytes);
}

void OperandStack::pushByte(int8_t value) {
    pushSingleByte(value);
}

void OperandStack::pushShort(int16_t value) {
    pushSingleByte(value);
}

void OperandStack::pushInt(int32_t value) {
    pushSingleByte(value);
}

void OperandStack::pushLong(int64_t value) {
    pushDoubleByte(value);
}

void OperandStack::pushFloat(float value) {
    int32_t *sv = reinterpret_cast<int32_t*>(&value);
    ;
    pushSingleByte(*sv);
}

void OperandStack::pushDouble(double value) {
    int64_t *sv = reinterpret_cast<int64_t*>(&value);
    pushDoubleByte(*sv);
}

void OperandStack::pushChar(uint16_t value) {
    pushSingleByte(value);
}

int8_t OperandStack::popByte() {
    return popSingleByte();
}

int16_t OperandStack::popShort() {
    return popSingleByte();
}

int32_t OperandStack::popInt() {
    return popSingleByte();
}

int64_t OperandStack::popLong() {
    return popDoubleByte();
}

float OperandStack::popFloat() {
    int32_t sv = popSingleByte();
    return *reinterpret_cast<float*>(&sv);
}

double OperandStack::popDouble() {
    int64_t sv = popDoubleByte();
    return *reinterpret_cast<double*>(&sv);
}

uint16_t OperandStack::popChar() {
    return popSingleByte();
}
