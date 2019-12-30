#include "format/constants/shared_constant_types.h"

using namespace avm;

SingleReference::SingleReference(const u2& index)
:_index(index){

}


ClassPropertyRef::ClassPropertyRef(const u2& classIndex, const u2& nameAndTypeIndex)
:_classIndex(classIndex), _nameAndTypeIndex(nameAndTypeIndex) {

}

SinglePrecisionNumber::SinglePrecisionNumber(const u4& bytes)
: _bytes(bytes){

}

DoublePrecisionNumber::DoublePrecisionNumber(const u4& highBytes, const u4& lowBytes)
:_highBytes(highBytes), _lowBytes(lowBytes){

}
