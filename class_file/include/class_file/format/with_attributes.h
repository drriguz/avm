#ifndef _AVM_WITH_ATTRIBUTE_INFO_H_
#define _AVM_WITH_ATTRIBUTE_INFO_H_

#include "types.h"
#include "attribute_info.h"

namespace avm {

class WithAttributes {
public:
	WithAttributes();
	virtual ~WithAttributes();
public:
	inline const u2& getAttributesCount() const { return _attributesCount; }
	const AttributeInfo* getAttributeAt(const u2& index) const;
protected:
	void initializeAttributes();
protected:
	u2 _attributesCount;
	AttributeInfo* _attributes;
};
}

#endif
