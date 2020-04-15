#include "class_file/format/constant/name_and_type.h"

#include <iostream>

using namespace avm;

ConstantNameAndType::ConstantNameAndType(const u2 nameIndex,
        const u2 descriptorIndex) :
    _nameIndex(nameIndex),
    _descriptorIndex(descriptorIndex),
    ConstantInfo(ConstantType::CONSTANT_NameAndType) {

}

