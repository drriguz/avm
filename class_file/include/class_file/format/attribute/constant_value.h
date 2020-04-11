#ifndef _AVM_CONSTANT_VALUE_ATTRIBUTE_H_
#define _AVM_CONSTANT_VALUE_ATTRIBUTE_H_

#include "class_file/format/attribute/attribute_info.h"

namespace avm {

class ConstantValue: public AttributeInfo {
public:
    ConstantValue(const u2 &valueIndex);
    virtual ~ConstantValue();
public:
    inline const u2 getValueIndex() const {
        return _valueIndex;
    }
protected:
    const u2 _valueIndex;
};

}

#endif
