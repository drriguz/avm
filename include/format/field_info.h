#ifndef _AVM_FIELD_INFO_H_
#define _AVM_FIELD_INFO_H_

#include "attribute_info.h"

namespace avm {
class FieldInfo {
	friend class ClassParser;
public:
	~FieldInfo();
public:
	void ensureAttributes();
private:
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	AttributeInfo* attributes;
};
}
#endif
