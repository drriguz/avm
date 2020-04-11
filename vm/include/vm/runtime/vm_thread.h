#ifndef _AVM_VM_THREAD_H_
#define _AVM_VM_THREAD_H_

#include "vm_stack.h"
#include "vm_class.h"
#include "vm_method.h"

namespace avm {

class VmThread {
public:
    VmThread(const VmClass* entryClass, const VmMethod* entryMethod);
    virtual ~VmThread();
public:
    Frame* currentFrame();
    const Instruction* nextInstruction();
protected:
    int _pcRegister;
    VmStack _vmStack;
    const VmClass* _entryClass;
    const VmMethod* _entryMethod;
};
}
#endif
