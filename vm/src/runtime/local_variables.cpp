#include "vm/runtime/local_variables.h"
#include "vm/util/numbers.h"
#include "vm/exceptions.h"

#include <iostream>

using namespace avm;

LocalVariables::LocalVariables(int size) :
    _size(size),
    _variables(new SLOT[size]) {

}

LocalVariables::~LocalVariables() {
    delete[] _variables;
}

void LocalVariables::checkRange(int i, int valueSize) {
    int lastIndex = i + valueSize - 1;
    if (i < 0 || lastIndex >= _size)
        throw LocalVariablesOutOfRangeException("Index out of range");
}

void LocalVariables::setSingleByte(int i, int32_t value) {
    checkRange(i, 1);
    uint32_t *uv = reinterpret_cast<uint32_t*>(&value);
    _variables[i] = *uv;
}

void LocalVariables::setDoubleByte(int i, int64_t value) {
    checkRange(i, 2);
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
    _variables[i] = highBytes;
    _variables[i + 1] = lowBytes;
}

int32_t LocalVariables::getSingleByte(int i) {
    checkRange(i, 1);
    return _variables[i];
}

int64_t LocalVariables::getDoubleByte(int i) {
    checkRange(i, 2);
    uint32_t highBytes = _variables[i], lowBytes = _variables[i + 1];
    return Numbers::asLong(highBytes, lowBytes);
}

void LocalVariables::setByte(int i, int8_t value) {
    setSingleByte(i, value);
}

void LocalVariables::setShort(int i, int16_t value) {
    setSingleByte(i, value);
}

void LocalVariables::setInt(int i, int32_t value) {
    setSingleByte(i, value);
}

void LocalVariables::setLong(int i, int64_t value) {
    setDoubleByte(i, value);
}

void LocalVariables::setFloat(int i, float value) {
    int32_t *sv = reinterpret_cast<int32_t*>(&value);
    setSingleByte(i, *sv);
}

void LocalVariables::setDouble(int i, double value) {
    int64_t *sv = reinterpret_cast<int64_t*>(&value);
    setDoubleByte(i, *sv);
}

void LocalVariables::setChar(int i, uint16_t value) {
    int32_t *sv = reinterpret_cast<int32_t*>(&value);
    setSingleByte(i, *sv);
}

void LocalVariables::dump() const {
    std::cout << "\tVARS : " << _size << std::endl;
}

int8_t LocalVariables::getByte(int i) {
    return getSingleByte(i);
}

int16_t LocalVariables::getShort(int i) {
    return getSingleByte(i);
}

int32_t LocalVariables::getInt(int i) {
    return getSingleByte(i);
}

int64_t LocalVariables::getLong(int i) {
    return getDoubleByte(i);
}

float LocalVariables::getFloat(int i) {
    int32_t intValue = getSingleByte(i);
    return *reinterpret_cast<float*>(&intValue);
}

double LocalVariables::getDouble(int i) {
    int64_t intValue = getDoubleByte(i);
    return *reinterpret_cast<double*>(&intValue);
}

uint16_t LocalVariables::getChar(int i) {
    int32_t intValue = getSingleByte(i);
    return *reinterpret_cast<uint16_t*>(&intValue);
}

reference LocalVariables::getReference(int i) {
#ifdef _ARCH_X64_
    return getDoubleByte(i);
#else
    return getSingleByte(i);
#endif
}

void LocalVariables::setReference(int i, reference value) {
#ifdef _ARCH_X64_
    setDoubleByte(i, value);
#else
    setSingleByte(i, value);
#endif
}
void LocalVariables::initialize(OperandStack* stack, std::vector<std::unique_ptr<FieldType>> paramTypes) {
    for(int i = 0; i < paramTypes.size(); i++) {
        auto type = paramTypes.at(i).get();
        if(type->isBaseType()) {
            switch(type->as<BaseType>()->getType()) {
            case FIELD_Byte:
            case FIELD_Short:
            case FIELD_Char:
            case FIELD_Int:
            case FIELD_Boolean: {
                setInt(i, stack->popInt());
                break;
            }
            case FIELD_Float: {
                setFloat(i, stack->popFloat());
                break;
            }
            case FIELD_Long: {
                setLong(i, stack->popLong());
                break;
            }
            case FIELD_Double: {
                setDouble(i, stack->popDouble());
                break;
            }
            default:
                break;
            }
        } else if(type->isObject()) {
            setReference(i, stack->popReference());
        } else {
            // fixme: support array type
            setReference(i, stack->popReference());
        }
    }
}