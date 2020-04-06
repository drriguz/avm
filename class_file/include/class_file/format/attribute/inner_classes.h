#ifndef _AVM_INNER_CLASSES_ATTRIBUTE_H_
#define _AVM_INNER_CLASSES_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class InnerClasses: public AttributeInfo {
public:
	InnerClasses();
	virtual ~InnerClasses();
};

}

#endif
