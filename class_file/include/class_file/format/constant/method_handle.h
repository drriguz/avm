#ifndef _AVM_CONSTANT_METHOD_HANDLE_H_
#define _AVM_CONSTANT_METHOD_HANDLE_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantMethodHandle: public ConstantInfo {
public:
    ConstantMethodHandle(const u1 referenceKind, const u2 referenceIndex);
public:
    inline const u1 getReferenceKind() const {
        return _referenceKind;
    }
    inline const u2 getReferenceIndex() const {
        return _referenceIndex;
    }
private:
    const u1 _referenceKind;
    const u1 _referenceIndex;
};

}
#endif
