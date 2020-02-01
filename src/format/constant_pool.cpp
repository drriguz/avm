#include "format/constant_pool.h"

#include <iostream>

using namespace avm;

CClass::CClass(const u2& nameIndex)
:_nameIndex(nameIndex), Constant(ConstantType::Class){

}

