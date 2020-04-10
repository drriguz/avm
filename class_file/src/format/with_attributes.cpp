#include "class_file/format/with_attributes.h"
#include "class_file/exceptions.h"

using namespace avm;

WithAttributes::WithAttributes() :
        _attributesCount(0) {

}

WithAttributes::~WithAttributes() {

}

void WithAttributes::addAttribute(AttributeInfo* attribute) {
    _attributes.push_back(std::unique_ptr<AttributeInfo>(attribute));
}

const AttributeInfo* WithAttributes::getAttributeAt(const u2 &index) const {
    if ((index < 0) || (index >= _attributesCount))
        throw new RuntimeException("Index out of bound");
    return _attributes[index].get();
}
