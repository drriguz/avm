#ifndef _AVM_ATTRIBUTE_INFO_H_
#define _AVM_ATTRIBUTE_INFO_H_

#include "class_file/format/types.h"
#include "class_file/format/constant_pool.h"

namespace avm {

class AttributeInfo {
public:
	AttributeInfo(u2 nameIndex);
	virtual ~AttributeInfo();
protected:
	u2 _nameIndex;
	ConstantPool* _constantPool;
protected:
	AttributeInfo(AttributeInfo&&) {};
	AttributeInfo(const AttributeInfo&) {};
	AttributeInfo& operator=(const AttributeInfo&) {};
};

}

#endif
