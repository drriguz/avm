#ifndef _AVM_CLASS_PROPERTY_INFO_H_
#define _AVM_CLASS_PROPERTY_INFO_H_

#include "types.h"
#include "attribute_info.h"
#include "access_flags.h"
#include "with_attributes.h"

namespace avm {

class ClassProperty: public WithAttributes {
public:
	ClassProperty();
	virtual ~ClassProperty();
public:
	inline const u2& getAccessFlags() const { return _accessFlags; }
	inline const u2& getNameIndex() const { return _nameIndex; }
	inline const u2& getDescriptorIndex() const { return _descriptorIndex; }
public:
	inline bool isPublic() const { return _accessFlags & ACC_PUBLIC; }
	inline bool isPrivate() const { return _accessFlags & ACC_PRIVATE; }
	inline bool isProtected() const { return _accessFlags & ACC_PROTECTED; }
	inline bool isStatic() const { return _accessFlags & ACC_STATIC; }
	inline bool isFinal() const { return _accessFlags & ACC_FINAL; }
	inline bool isSynthetic() const { return _accessFlags & ACC_SYNTHETIC; }
protected:
	u2 _accessFlags;
	u2 _nameIndex;
	u2 _descriptorIndex;
};
}

#endif
