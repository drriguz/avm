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

const AttributeInfo* WithAttributes::getAttributeAt(const u2 index) const {
    if ((index < 0) || (index >= _attributesCount))
        throw RuntimeException("Index out of bound");
    return _attributes[index].get();
}

const AttributeInfo* WithAttributes::getAttrinute(AttributeType type) const {
    const AttributeInfo* attribute = getAttrinuteIfPresent(type);
    if(attribute == nullptr)
        throw AttributeNotFoundException("No enum found with the type");
    return attribute;
}

const AttributeInfo* WithAttributes::getAttrinuteIfPresent(AttributeType type) const {
    for (auto it = _attributes.begin() ; it != _attributes.end(); ++it) {
        if((*it).get()->getType() == type)
            return (*it).get();
    }
    return nullptr;
}