#include "vm/runtime/local_variables.h"
#include "vm/util/numbers.h"
#include "vm/exceptions.h"

using namespace avm;

LocalVariables::LocalVariables(int size) :
    _size(size),
    _variables(new Slot*[size]()) {

}

LocalVariables::~LocalVariables() {
    for (int i = 0; i < _size; i++)
        if (_variables[i])
            delete _variables[i];
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
    if (_variables[i])
        delete _variables[i];
    _variables[i] = new Slot(*uv);
}

void LocalVariables::setDoubleByte(int i, int64_t value) {
    checkRange(i, 2);
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
    if (_variables[i]) {
        delete _variables[i];
        delete _variables[i + 1];
    }
    _variables[i] = new Slot(highBytes);
    _variables[i + 1] = new Slot(lowBytes);
}

int32_t LocalVariables::getSingleByte(int i) {
    checkRange(i, 1);
    return _variables[i]->asInt();
}

int64_t LocalVariables::getDoubleByte(int i) {
    checkRange(i, 2);
    uint32_t highBytes = _variables[i]->getValue(), lowBytes =
                             _variables[i + 1]->getValue();
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
