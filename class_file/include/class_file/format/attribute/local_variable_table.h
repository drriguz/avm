#ifndef _AVM_LOCAL_VARIABLE_TABLE_ATTRIBUTE_H_
#define _AVM_LOCAL_VARIABLE_TABLE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class LocalVariableTable: public AttributeInfo {
public:
	LocalVariableTable();
	virtual ~LocalVariableTable();
};

}

#endif
