#ifndef _AVM_SIGNATURE_ATTRIBUTE_H_
#define _AVM_SIGNATURE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class Signature: public AttributeInfo {
public:
	Signature();
	virtual ~Signature();
};

}

#endif
