#ifndef _AVM_CONSTANT_VALUE_ATTRIBUTE_H_
#define _AVM_CONSTANT_VALUE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class ConstantValue: public AttributeInfo {
public:
	ConstantValue(const u2& valueIndex):_valueIndex(valueIndex){};
	virtual ~ConstantValue(){};
protected:
	const u2 _valueIndex;
};

}

#endif
