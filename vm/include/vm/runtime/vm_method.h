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
    u2 getInstructionsCount() const;
    const Instruction* getInstruction(u2 index) const;
protected:
    const std::string _name;
    const std::string _descriptor;
    const MethodInfo* _javaMethod;
    const bool _isNative;
};
}

#endif