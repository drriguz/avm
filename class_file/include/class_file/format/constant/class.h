#ifndef _AVM_CONSTANT_CLASS_H_
#define _AVM_CONSTANT_CLASS_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantClass: public ConstantInfo {
public:
    ConstantClass(const u2 nameIndex);
public:
    inline u2 getNameIndex() const {
        return _nameIndex;
    }
private:
    const u2 _nameIndex;
};

}
#endif
