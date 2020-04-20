#include "vm/runtime/vm_field.h"
#include "vm/util/numbers.h"

#include "vm/exceptions.h"

using namespace avm;

VmField::VmField(const std::string& name, const FieldDescriptor& descriptor, const int fieldId, const bool isStatic, Slot* slot1, Slot* slot2)
    : _name(name),
      _fieldId(fieldId),
      _descriptor(descriptor),
      _isStatic(isStatic),
      _slot1(slot1),
      _slot2(slot2) {
}

std::unique_ptr<VmField> VmField::newStaticField(const std::string& name, const std::string& descriptor) {
    FieldDescriptor type(descriptor);
    Slot* slot2 = nullptr;
    if(type.isDoubleBytes())
        slot2 = new Slot(0);
    return std::unique_ptr<VmField>(new VmField(name, descriptor, -1, true, new Slot(0), slot2));
}

std::unique_ptr<VmField> VmField::newInstanceField(const std::string& name, const std::string& descriptor, const int fieldId) {
    return  std::unique_ptr<VmField>(new VmField(name, descriptor, fieldId, false, nullptr, nullptr));
}

VmField::~VmField() {
    if(_isStatic) {
        if(_slot1) {
            delete _slot1;
            _slot1 = nullptr;
        }
        if(_slot2) {
            delete _slot2;
            _slot2 = nullptr;
        }
    }
}

void VmField::setByte(int8_t value) {
    *_slot1 = value;
}
void VmField::setShort(int16_t value) {
    *_slot1 = value;
}
void VmField::setInt(int32_t value) {
    *_slot1 = value;
}
void VmField::setLong(int64_t value) {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitLong(value);
    *_slot1 = highBytes;
    *_slot2 = lowBytes;
}
void VmField::setFloat(float value) {
    int32_t *sv = reinterpret_cast<int32_t*>(&value);
    *_slot1 = *sv;
}
void VmField::setDouble(double value) {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes, lowBytes;
    std::tie(highBytes, lowBytes) = Numbers::splitDouble(value);
    *_slot1 = highBytes;
    *_slot2 = lowBytes;
}
void VmField::setChar(uint16_t value) {
    *_slot1 = value;
}

void VmField::setReference(int64_t value) {
    setLong(value);
}

int8_t VmField::getByte() const {
    return _slot1->asInt();
}
int16_t VmField::getShort() const {
    return _slot1->asInt();
}
int32_t VmField::getInt() const {
    return _slot1->asInt();
}
int64_t VmField::getLong() const {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes = _slot1->asInt();
    uint32_t lowBytes = _slot2->asInt();
    return Numbers::asLong(highBytes, lowBytes);
}
float VmField::getFloat() const {
    return _slot1->asFloat();
}
double VmField::getDouble() const {
    if(!_descriptor.isDoubleBytes())
        throw FieldValueTypeNotMatchException("Require two bytes type");
    uint32_t highBytes = _slot1->asInt();
    uint32_t lowBytes = _slot2->asInt();
    return Numbers::asDouble(highBytes, lowBytes);
}
uint16_t VmField::getChar() const {
    return _slot1->asInt();
}

std::string VmField::getString() const {
    return *reinterpret_cast<const std::string*>(getLong());
}

int VmField::getFieldSlotsSize() const {
    // todo: should reference return 2?
    if(_descriptor.isDoubleBytes())
        return 2;
    else
        return 1;
}