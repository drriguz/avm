#ifndef _AVM_CONSTANT_REF_H_
#define _AVM_CONSTANT_REF_H_

#include <string>

#include "constant_info.h"

namespace avm {

class ConstantRef: public ConstantInfo {
public:
    ConstantRef(const ConstantType &type,
                const u2 classIndex,
                const u2 nameAndTypeIndex);
public:
    inline u2 getClassIndex() const {
        return _classIndex;
    }
    inline u2 getNameAndTypeIndex() const {
        return _nameAndTypeIndex;
    }
protected:
    u2 _classIndex;
    u2 _nameAndTypeIndex;
};

class ConstantFieldref: public ConstantRef {
public:
    ConstantFieldref(const u2 classIndex, const u2 nameAndTypeIndex);
};

class ConstantMethodref: public ConstantRef {
public:
    ConstantMethodref(const u2 classIndex, const u2 nameAndTypeIndex);
};

class ConstantInterfaceMethodref: public ConstantRef {
public:
    ConstantInterfaceMethodref(const u2 classIndex,
                               const u2 nameAndTypeIndex);
};
}
#endif
