#ifndef _AVM_CODE_ATTRIBUTE_H_
#define _AVM_CODE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class Code: public AttributeInfo {
public:
    Code() {
    }
    virtual ~Code() {
    }
protected:
    const u2 _maxStack;
    const u2 _maxLocals;
    const u4 _codeLength;
};

}

#endif
