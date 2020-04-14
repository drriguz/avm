#ifndef _AVM_CONSTANT_NAME_AND_TYPE_H_
#define _AVM_CONSTANT_NAME_AND_TYPE_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantNameAndType: public ConstantInfo {
public:
    ConstantNameAndType(const u2 nameIndex, const u2 descriptorIndex);
public:
    inline const u2 getNameIndex() const {
        return _nameIndex;
    }
    inline const u2 getDescriptorIndex() const {
        return _descriptorIndex;
    }
private:
    u2 _nameIndex;
    u2 _descriptorIndex;
};

}
#endif
