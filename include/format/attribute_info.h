#ifndef _AVM_ATTRIBUTE_INFO_H_
#define _AVM_ATTRIBUTE_INFO_H_

#include "types.h"

namespace avm {
class AttributeInfo {
	friend class ClassParser;
public:
	~AttributeInfo();
public:
	void ensureAttributes();
private:
	u2 attribute_name_index;
	u2 attribute_length;
	u1* info;
};
}
#endif
