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
    inline int size() const {
        return _frames.size();
    }
    void push(std::unique_ptr<Frame> frame);
    void pop();
    Frame* currentFrame() const;
protected:
    std::stack<std::unique_ptr<Frame>> _frames;
};
}
#endif
