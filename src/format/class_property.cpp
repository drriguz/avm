#include "format/class_property.h"
#include "exceptions.h"

using namespace avm;

ClassProperty::ClassProperty()
:_accessFlags(0),
 _nameIndex(0),
 _descriptorIndex(0),
 _attributesCount(0),
 _attributes(nullptr){

}

ClassProperty::~ClassProperty(){
	if(_attributes) {
		delete[] _attributes;
		_attributes = nullptr;
	}
}

void ClassProperty::initializeAttributes() {
	if(_attributes) {
		delete[] _attributes;
		_attributes = nullptr;
	}
	if(_attributesCount > 0)
		_attributes = new AttributeInfo[_attributesCount];
}

const AttributeInfo* ClassProperty::getAttributeAt(const u2& index) const{
	if((index < 0) || (index >= _attributesCount))
		throw new RuntimeException("Index out of bound");
	return &_attributes[index];
}
