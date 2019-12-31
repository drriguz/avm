#ifndef _AVM_FIELD_INFO_H_
#define _AVM_FIELD_INFO_H_

#include "types.h"
#include "class_property.h"

namespace avm {

class FieldInfo: public ClassProperty {
	friend class JavaClassParser;
public:
	FieldInfo();
	virtual ~FieldInfo();
public:
	inline bool isVolatile() const { return _accessFlags & ACC_VOLATILE; }
	inline bool isTransient() const { return _accessFlags & ACC_TRANSIENT; }
	inline bool isEnum() const { return _accessFlags & ACC_ENUM; }
};
}

#endif
