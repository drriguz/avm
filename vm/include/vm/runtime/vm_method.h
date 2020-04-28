#ifndef _AVM_VM_METHOD_H_
#define _AVM_VM_METHOD_H_

#include "class_file/format/method_info.h"

namespace avm {
class VmClass;

class VmMethod {
public:
    VmMethod(const MethodInfo* method, const VmClass* methodClass);
    virtual ~VmMethod();
public:
    inline std::string getName() const {
        return _name;
    }
    inline std::string getDescriptor() const {
        return _descriptor;
    }
    inline const VmClass* getClass() const {
        return _class;
    }
    u2 getMaxLocals() const;
    u2 getMaxStack() const;
    u2 getInstructionsCount() const;
    const Instruction* getInstruction(u2 index) const;
protected:
    const VmClass* _class;
    const std::string _name;
    const std::string _descriptor;
    const MethodInfo* _javaMethod;
    const bool _isNative;
};
}

#endif