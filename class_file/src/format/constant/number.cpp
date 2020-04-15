#include "class_file/format/constant/number.h"

#include <iostream>

using namespace avm;

ConstantInteger::ConstantInteger(const u4 bytes) :
    _bytes(bytes),
    ConstantInfo(ConstantType::CONSTANT_Integer) {

}

ConstantFloat::ConstantFloat(const u4 bytes) :
    _bytes(bytes),
    ConstantInfo(ConstantType::CONSTANT_Float) {

}

ConstantLong::ConstantLong(const u4 highBytes, const u4 lowBytes) :
    _highBytes(highBytes),
    _lowBytes(lowBytes),
    ConstantInfo(ConstantType::CONSTANT_Long) {

}

ConstantDouble::ConstantDouble(const u4 highBytes, const u4 lowBytes) :
    _highBytes(highBytes),
    _lowBytes(lowBytes),
    ConstantInfo(ConstantType::CONSTANT_Double) {

}

