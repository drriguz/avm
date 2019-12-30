#include "format/constants/constant_types.h"

using namespace avm;

ConstantClass::ConstantClass(const u2& classIndex)
: SingleReference(classIndex) {

}

ConstantFieldref::ConstantFieldref(const u2& classIndex, const u2& nameAndTypeIndex)
: ClassPropertyRef(classIndex, nameAndTypeIndex) {

}

ConstantMethodref::ConstantMethodref(const u2& classIndex, const u2& nameAndTypeIndex)
: ClassPropertyRef(classIndex, nameAndTypeIndex) {

}

ConstantInterfaceMethodref::ConstantInterfaceMethodref(const u2& classIndex, const u2& nameAndTypeIndex)
: ClassPropertyRef(classIndex, nameAndTypeIndex) {

}

ConstantString::ConstantString(const u2& classIndex)
: SingleReference(classIndex) {

}

ConstantInteger::ConstantInteger(const u4& bytes)
: SinglePrecisionNumber(bytes) {

}

ConstantFloat::ConstantFloat(const u4& bytes)
: SinglePrecisionNumber(bytes) {

}

ConstantLong::ConstantLong(const u4& highBytes, const u4& lowBytes)
: DoublePrecisionNumber(highBytes, lowBytes) {

}

ConstantDouble::ConstantDouble(const u4& highBytes, const u4& lowBytes)
: DoublePrecisionNumber(highBytes, lowBytes) {

}

