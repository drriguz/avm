#include "format/constant/class.h"

#include <iostream>

using namespace avm;

ConstantClass::ConstantClass(const u2& nameIndex)
:_nameIndex(nameIndex),
 ConstantInfo(ConstantType::Class){

}

