#ifndef _AVM_VM_METHOD_H_
#define _AVM_VM_METHOD_H_

#include "class_file/format/method_info.h"

namespace avm {

class VmMethod {
public:
    VmMethod(const MethodInfo* method) : _javaMethod(method) {

    }
    virtual ~VmMethod();
protected:
    const MethodInfo* _javaMethod;
};
}

#endif