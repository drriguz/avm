#include "vm/runtime/operand_stack.h"
#include "vm/exceptions.h"
#include "vm/util/numbers.h"

#include <iostream>

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
    _variables.push(*uv);
}

void OperandStack::pushDoubleByte(int64_t value) {
    checkStackSize(2);
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
    _variables.push(highBytes);
    _variables.push(lowBytes);
}

int32_t OperandStack::popSingleByte() {
    SLOT top = _variables.top();
    _variables.pop();
    return top;
}

int64_t OperandStack::popDoubleByte() {
    uint32_t lowBytes = _variables.top();
    _variables.pop();
    uint32_t highBytes = _variables.top();
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
    pushSingleByte(*sv);
}

void OperandStack::pushDouble(double value) {
    int64_t *sv = reinterpret_cast<int64_t*>(&value);
    pushDoubleByte(*sv);
}

void OperandStack::pushReference(reference value) {
#ifdef _ARCH_X64_
    pushSingleByte(value);
#else
    pushDoubleByte(value);
#endif
}

void OperandStack::pushChar(uint16_t value) {
    pushSingleByte(value);
}

void OperandStack::dump() const {
    std::cout << "STACK: " << _variables.size() << std::endl;
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

reference OperandStack::popReference() {
#ifdef _ARCH_X64_
    return popDoubleByte();
#else
    return popSingleByte();
#endif
}

void OperandStack::pushField(const VmField* source) {
    const FieldType* type = source->getDescriptor();
    if(type->isBaseType()) {
        switch(((BaseType*)type)->getType()) {
        case FIELD_Byte:
        case FIELD_Short:
        case FIELD_Char:
        case FIELD_Int:
        case FIELD_Boolean: {
            pushInt(source->getInt());
            break;
        }
        case FIELD_Float: {
            pushFloat(source->getFloat());
            break;
        }
        case FIELD_Long: {
            pushLong(source->getLong());
            break;
        }
        case FIELD_Double: {
            pushDouble(source->getDouble());
            break;
        }
        default:
            break;
        }
    } else if(type->isObject()) {
        pushReference(source->getReference());
    } else {
        throw "todo: support array type";
    }
}

void OperandStack::popField(VmField* field) {
    const FieldType* type = field->getDescriptor();
    if(type->isBaseType()) {
        switch(((BaseType*)type)->getType()) {
        case FIELD_Byte:
        case FIELD_Short:
        case FIELD_Char:
        case FIELD_Int:
        case FIELD_Boolean: {
            field->setInt(popInt());
            break;
        }
        case FIELD_Float: {
            field->setFloat(popFloat());
            break;
        }
        case FIELD_Long: {
            field->setLong(popLong());
            break;
        }
        case FIELD_Double: {
            field->setDouble(popDouble());
            break;
        }
        default:
            break;
        }
    } else if(type->isObject()) {
        field->setReference(popReference());
    } else {
        throw "todo: support array type";
    }
}