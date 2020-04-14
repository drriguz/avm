#include "class_file/format/attribute/constant_value.h"

using namespace avm;

ConstantValue::ConstantValue(const u2 &valueIndex) :
    _valueIndex(valueIndex),
    AttributeInfo(AttributeType::CONSTANT_VALUE) {
}

ConstantValue:: ~ConstantValue() {
}