#ifndef _AVM_THREAD_CONTEXT_H_
#define _AVM_THREAD_CONTEXT_H_

#include "virtual_machine.h"
#include "runtime/method_area.h"
#include "runtime/vm_method.h"


namespace avm {
class VmThread;
class VmStack;
class Frame;
class Context {
public:
    Context(VirtualMachine* jvm, VmStack* stack)
        : _stack(stack), _jvm(jvm), _method(nullptr) {}
    Context(VirtualMachine* jvm, VmStack* stack, const VmMethod* method)
        : _stack(stack), _jvm(jvm), _method(method) {}
    virtual ~Context() {}
public:
    inline VirtualMachine* getJVM() const {
        return _jvm;
    }
    inline VmStack* getStack() const {
        return _stack;
    }
    inline const VmMethod* getMethod() const {
        return _method;
    }
    inline Frame* frame() const {
        return _stack->currentFrame();
    }
    inline Frame* previousFrame() const {
        if(_stack->currentFrame() == nullptr)
            throw RuntimeException("Cannot get previous frame because current is null");
        return _stack->currentFrame()->getPreviousFrame();
    }
protected:
    VmStack* _stack;
    VirtualMachine* _jvm;
    const VmMethod* _method;
};
}
#endif