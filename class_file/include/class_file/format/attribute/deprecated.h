#ifndef _AVM_DEPRECATED_ATTRIBUTE_H_
#define _AVM_DEPRECATED_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class Deprecated: public AttributeInfo {
public:
	Deprecated();
	virtual ~Deprecated();
};

}

#endif
