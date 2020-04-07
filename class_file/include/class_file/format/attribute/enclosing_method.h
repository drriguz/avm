#ifndef _AVM_ENCLOSING_METHOD_ATTRIBUTE_H_
#define _AVM_ENCLOSING_METHOD_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class EnclosingMethod: public AttributeInfo {
public:
    EnclosingMethod();
    virtual ~EnclosingMethod();
};

}

#endif
