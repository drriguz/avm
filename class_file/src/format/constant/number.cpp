#include "class_file/format/constant/number.h"

#include <iostream>

using namespace avm;

ConstantInteger::ConstantInteger(const u4& bytes)
:_bytes(bytes),
 ConstantInfo(ConstantType::Integer){

}

ConstantFloat::ConstantFloat(const u4& bytes)
:_bytes(bytes),
 ConstantInfo(ConstantType::Float){

}

ConstantLong::ConstantLong(const u4& highBytes, const u4& lowBytes)
:_highBytes(highBytes),
 _lowBytes(lowBytes),
 ConstantInfo(ConstantType::Long){

}

ConstantDouble::ConstantDouble(const u4& highBytes, const u4& lowBytes)
:_highBytes(highBytes),
 _lowBytes(lowBytes),
 ConstantInfo(ConstantType::Double){

}

