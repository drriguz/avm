#ifndef _AVM_VM_METHOD_H_
#define _AVM_VM_METHOD_H_

#include "class_file/format/method_info.h"

namespace avm {

class VmMethod {
public:
    VmMethod(const MethodInfo* method);
    virtual ~VmMethod();
public:
    u2 getMaxLocals() const;
    u2 getMaxStack() const;
    const Instruction* getInstruction(u2 index) const;
protected:
    const MethodInfo* _javaMethod;
};
}

#endif