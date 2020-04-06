#ifndef _AVM_LINE_NUMBER_TABLE_ATTRIBUTE_H_
#define _AVM_LINE_NUMBER_TABLE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class LineNumberTable: public AttributeInfo {
public:
	LineNumberTable();
	virtual ~LineNumberTable();
};

}

#endif
