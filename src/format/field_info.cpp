#include "format/field_info.h"
using namespace avm;

FieldInfo::FieldInfo()
:_accessFlags(0),
 _nameIndex(0),
 _descriptorIndex(0),
 _attributesCount(0),
 _attributes(nullptr){

}

FieldInfo::~FieldInfo(){
	if(_attributes) {
		delete[] _attributes;
		_attributes = nullptr;
	}
}

void FieldInfo::initializeAttributes() {
	if(_attributes) {
		delete[] _attributes;
		_attributes = nullptr;
	}
	if(_attributesCount > 0)
		_attributes = new AttributeInfo[_attributesCount];
}
