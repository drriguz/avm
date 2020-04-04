#include "class_file/format/constant/method_type.h"

#include <iostream>

using namespace avm;

ConstantMethodType::ConstantMethodType(const u2& descriptorIndex)
:_descriptorIndex(descriptorIndex),
 ConstantInfo(ConstantType::MethodType){

}
