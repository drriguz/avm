#include "format/with_attributes.h"
#include "exceptions.h"

using namespace avm;

WithAttributes::WithAttributes()
:_attributesCount(0),
 _attributes(nullptr){

}

WithAttributes::~WithAttributes(){
	if(_attributes) {
		delete[] _attributes;
		_attributes = nullptr;
	}
}

void WithAttributes::initializeAttributes() {
	if(_attributes) {
		delete[] _attributes;
		_attributes = nullptr;
	}
	if(_attributesCount > 0)
		_attributes = new AttributeInfo[_attributesCount];
}

const AttributeInfo* WithAttributes::getAttributeAt(const u2& index) const{
	if((index < 0) || (index >= _attributesCount))
		throw new RuntimeException("Index out of bound");
	return &_attributes[index];
}
