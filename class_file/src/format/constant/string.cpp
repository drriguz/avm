#include "class_file/format/constant/string.h"

#include <iostream>

using namespace avm;

ConstantString::ConstantString(const u2 &stringIndex) :
        _stringIndex(stringIndex),
        ConstantInfo(ConstantType::String) {

}

