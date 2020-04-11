#include "class_file/format/attribute/exceptions.h"

using namespace avm;

Exceptions::Exceptions():
_exceptionsCount(0),
_indexes(nullptr),
AttributeInfo(AttributeType::EXCEPTIONS) {
}

Exceptions::~Exceptions() {
    if(_indexes) {
        delete[] _indexes;
        _indexes = nullptr;
    }
}