#ifndef _AVM_THREAD_CONTEXT_H_
#define _AVM_THREAD_CONTEXT_H_

#include "virtual_machine.h"
#include "runtime/frame.h"
#include "runtime/method_area.h"


namespace avm {
class Context {
public:
    Context(Frame* frame, VirtualMachine* jvm)
        : _frame(frame), _jvm(jvm) {}
    virtual ~Context() {}
public:
    inline Frame* frame() const {
        return _frame;
    }
    inline const VirtualMachine* getJVM() const {
        return _jvm;
    }
protected:
    Frame* _frame;
    VirtualMachine* _jvm;
};
}
#endif