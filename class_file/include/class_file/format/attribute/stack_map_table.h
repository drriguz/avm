#ifndef _AVM_STACK_MAP_TABLE_ATTRIBUTE_H_
#define _AVM_STACK_MAP_TABLE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class StackMapTable: public AttributeInfo {
public:
    StackMapTable();
    virtual ~StackMapTable();
};

}

#endif
