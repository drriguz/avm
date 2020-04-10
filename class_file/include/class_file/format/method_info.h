#ifndef _AVM_METHOD_INFO_H_
#define _AVM_METHOD_INFO_H_

#include "types.h"
#include "class_property.h"
#include "attributes.h"

namespace avm {

class MethodInfo: public ClassProperty {
    friend class JavaClassParser;
public:
    MethodInfo();
    virtual ~MethodInfo();
public:
    inline bool isSynchronized() const {
        return _accessFlags & ACC_SYNCHRONIZED;
    }
    inline bool isBridge() const {
        return _accessFlags & ACC_BRIDGE;
    }
    inline bool isVarages() const {
        return _accessFlags & ACC_VARARGS;
    }
    inline bool isNative() const {
        return _accessFlags & ACC_NATIVE;
    }
    inline bool isAbstract() const {
        return _accessFlags & ACC_ABSTRACT;
    }
    inline bool isStrict() const {
        return _accessFlags & ACC_STRICT;
    }
public:
    const Code* getCode() const;
};
}

#endif
