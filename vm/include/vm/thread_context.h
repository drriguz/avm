#ifndef _AVM_THREAD_CONTEXT_H_
#define _AVM_THREAD_CONTEXT_H_

#include "virtual_machine.h"
#include "runtime/vm_stack.h"
#include "runtime/method_area.h"


namespace avm {
class Context {
public:
    Context(VmStack* vmStack, VirtualMachine* jvm, const ConstantPool* constantPool)
        : _vmStack(vmStack), _jvm(jvm), _constantPool(constantPool) {}
    virtual ~Context() {}
public:
    inline const ConstantPool* constantPool() const {
        return _constantPool;
    }
    inline VmStack* getVmStack() const {
        return _vmStack;
    }
    inline Frame* frame() const {
        return _vmStack->currentFrame();
    }
    inline const VirtualMachine* getJVM() const {
        return _jvm;
    } 
protected:
    VmStack* _vmStack;
    VirtualMachine* _jvm;
    const ConstantPool* _constantPool;
};
}
#endif