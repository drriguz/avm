#ifndef _AVM_SYNTHETIC_ATTRIBUTE_H_
#define _AVM_SYNTHETIC_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class Synthetic: public AttributeInfo {
public:
	Synthetic();
	virtual ~Synthetic();
};

}

#endif
