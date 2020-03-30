#include "format/constant/method_handle.h"

#include <iostream>

using namespace avm;

ConstantMethodHandle::ConstantMethodHandle(const u1& referenceKind, const u2& referenceIndex)
:_referenceKind(referenceKind),
 _referenceIndex(referenceIndex),
 ConstantInfo(ConstantType::MethodHandle){

}
