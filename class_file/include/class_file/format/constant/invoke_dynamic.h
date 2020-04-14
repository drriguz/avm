#ifndef _AVM_CONSTANT_INVOKE_DYNAMIC_H_
#define _AVM_CONSTANT_INVOKE_DYNAMIC_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantInvokeDynamic: public ConstantInfo {
public:
    ConstantInvokeDynamic(const u2 bootstrapMethodAttrIndex,
                          const u2 nameAndTypeIndex);
public:
    inline const u2 getNameAndTypeIndex() const {
        return _nameAndTypeIndex;
    }
    inline const u2 getBootstrapMethodAttrIndex() const {
        return _bootstrapMethodAttrIndex;
    }
private:
    const u2 _bootstrapMethodAttrIndex;
    const u2 _nameAndTypeIndex;
};

}
#endif
