#include "class_file/format/attribute/attribute_info.h"

using namespace avm;

AttributeInfo::AttributeInfo(u2 nameIndex) :
        _nameIndex(nameIndex) {
}

AttributeInfo::~AttributeInfo() {
}
