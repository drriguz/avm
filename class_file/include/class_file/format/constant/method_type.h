#ifndef _AVM_CONSTANT_METHOD_TYPE_H_
#define _AVM_CONSTANT_METHOD_TYPE_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantMethodType: public ConstantInfo {
public:
    ConstantMethodType(const u2 descriptorIndex);
public:
    inline const u2 getDescriptorIndex() const {
        return _descriptorIndex;
    }
private:
    const u2 _descriptorIndex;
};

}
#endif
