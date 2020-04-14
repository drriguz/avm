#ifndef _AVM_CONSTANT_STRING_H_
#define _AVM_CONSTANT_STRING_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantString: public ConstantInfo {
public:
    ConstantString(const u2 stringIndex);
public:
    inline const u2 getStringIndex() const {
        return _stringIndex;
    }
private:
    const u2 _stringIndex;
};

}
#endif
