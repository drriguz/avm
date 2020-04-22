#include "vm/runtime/vm_field.h"
#include "vm/util/numbers.h"

#include "vm/exceptions.h"

using namespace avm;

VmField::VmField(const std::string& name, const FieldDescriptor& descriptor, const int offset, const bool isStatic, uint32_t value1, uint32_t value2)
    : _name(name),
      _offset(offset),
      _descriptor(descriptor),
      _isStatic(isStatic),
      _value1(value1),
      _value2(value2) {
}

std::unique_ptr<VmField> VmField::newStaticField(const std::string& name, const std::string& descriptor) {
    FieldDescriptor type(descriptor);
    return std::unique_ptr<VmField>(new VmField(name, descriptor, -1, true, 0, 0));
}

std::unique_ptr<VmField> VmField::newInstanceField(const std::string& name, const std::string& descriptor, const int fieldId) {
    return  std::unique_ptr<VmField>(new VmField(name, descriptor, fieldId, false, 0, 0));
}

VmField::~VmField() {
}

void VmField::setByte(int8_t value) {
    _value1 = value;
}
void VmField::setShort(int16_t value) {
    _value1 = value;
}
void VmField::setInt(int32_t value) {
    _value1 = value;
}
void VmField::setLong(int64_t value) {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
    _value1 = highBytes;
    _value2 = lowBytes;
}
void VmField::setFloat(float value) {
    int32_t *sv = reinterpret_cast<int32_t*>(&value);
    _value1 = *sv;
}
void VmField::setDouble(double value) {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitDouble(value);
    _value1 = highBytes;
    _value2 = lowBytes;
}
void VmField::setChar(uint16_t value) {
    _value1 = value;
}

void VmField::setReference(reference value) {
    if(sizeof(reference) == 8)
        setLong(value);
    else
        setInt(value);
}

int8_t VmField::getByte() const {
    uint32_t copy = _value1;
    return *reinterpret_cast<int32_t*>(&copy);
}
int16_t VmField::getShort() const {
    uint32_t copy = _value1;
    return *reinterpret_cast<int32_t*>(&copy);
}
int32_t VmField::getInt() const {
    uint32_t copy = _value1;
    return *reinterpret_cast<int32_t*>(&copy);
}
int64_t VmField::getLong() const {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes = _value1;
    uint32_t lowBytes = _value2;
    return Numbers::asLong(highBytes, lowBytes);
}
float VmField::getFloat() const {
    uint32_t copy = _value1;
    return *reinterpret_cast<float*>(&copy);
}
double VmField::getDouble() const {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes = _value1;
    uint32_t lowBytes = _value2;
    return Numbers::asDouble(highBytes, lowBytes);
}
uint16_t VmField::getChar() const {
    return _value1;
}

std::string VmField::getString() const {
    return *reinterpret_cast<const std::string*>(getLong());
}

int VmField::getFieldSize() const {
    if(_descriptor.isDoubleBytes())
        return 2;
    else
        return 1;
}