#ifndef _AVM_FIELD_INFO_H_
#define _AVM_FIELD_INFO_H_

#include "types.h"
#include "attribute_info.h"
#include "access_flags.h"

namespace avm {
class JavaClassParser;

class FieldInfo {
	friend class JavaClassParser;
public:
	FieldInfo();
	virtual ~FieldInfo();
public:
	inline const u2& getAccessFlags() const { return _accessFlags; }
	inline const u2& getNameIndex() const { return _nameIndex; }
	inline const u2& getDescriptorIndex() const { return _descriptorIndex; }
	inline const u2& getAttributesCount() const { return _attributesCount; }
public:
	inline bool isPublic() const { return _accessFlags & ACC_PUBLIC; }
	inline bool isPrivate() const { return _accessFlags & ACC_PRIVATE; }
	inline bool isProtected() const { return _accessFlags & ACC_PROTECTED; }
	inline bool isStatic() const { return _accessFlags & ACC_STATIC; }
	inline bool isFinal() const { return _accessFlags & ACC_FINAL; }
	inline bool isVolatile() const { return _accessFlags & ACC_VOLATILE; }
	inline bool isTransient() const { return _accessFlags & ACC_TRANSIENT; }
	inline bool isSynthetic() const { return _accessFlags & ACC_SYNTHETIC; }
	inline bool isEnum() const { return _accessFlags & ACC_ENUM; }
protected:
	u2 _accessFlags;
	u2 _nameIndex;
	u2 _descriptorIndex;
	u2 _attributesCount;
	AttributeInfo* _attributes;
};
}

#endif
