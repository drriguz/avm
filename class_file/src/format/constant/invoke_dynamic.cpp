#include "class_file/format/constant/invoke_dynamic.h"

#include <iostream>

using namespace avm;

ConstantInvokeDynamic::ConstantInvokeDynamic(const u2 bootstrapMethodAttrIndex,
        const u2 nameAndTypeIndex) :
    _bootstrapMethodAttrIndex(bootstrapMethodAttrIndex),
    _nameAndTypeIndex(nameAndTypeIndex),
    ConstantInfo(ConstantType::CONSTANT_InvokeDynamic) {

}
