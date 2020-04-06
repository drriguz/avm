#ifndef _AVM_EXCEPTIONS_ATTRIBUTE_H_
#define _AVM_EXCEPTIONS_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class Exceptions: public AttributeInfo {
public:
	Exceptions();
	virtual ~Exceptions();
};

}

#endif
