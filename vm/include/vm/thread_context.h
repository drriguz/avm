#ifndef _AVM_THREAD_CONTEXT_H_
#define _AVM_THREAD_CONTEXT_H_

#include "virtual_machine.h"
#include "runtime/vm_thread.h"


namespace avm {
class Context {
public:
    Context(VirtualMachine* jvm, VmThread* thread): _jvm(jvm), _thread(thread) {}
    virtual ~Context() {}
public:
    inline VirtualMachine* vm() {
        return _jvm;
    }
    inline VmThread* thread() {
        return _thread;
    }
    inline Frame* frame() {
        return _thread->currentFrame();
    }
    inline const ConstantPool* constantPool() const {
        return _thread->currentClass()->getRuntimeConstantPool();
    }
protected:
    VirtualMachine* _jvm;
    VmThread* _thread;
};
}
#endif