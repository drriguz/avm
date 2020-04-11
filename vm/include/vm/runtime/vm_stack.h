#ifndef _AVM_VM_STACK_H_
#define _AVM_VM_STACK_H_

#include <stack>
#include <memory>

#include "frame.h"

namespace avm {

class VmStack {
public:
    VmStack();
    virtual ~VmStack();
public:
    void push(Frame* frame);
    void pop();
    Frame* currentFrame();
protected:
    std::stack<std::unique_ptr<Frame>> _frames;
};
}
#endif
