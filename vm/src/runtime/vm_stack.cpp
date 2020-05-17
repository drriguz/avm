#include "vm/runtime/vm_stack.h"

using namespace avm;

VmStack::VmStack() {

}

VmStack::~VmStack() {

}

void VmStack::push(std::unique_ptr<Frame> frame) {
    _frames.push(std::move(frame));
}
void VmStack::pop() {
    _frames.pop();
}
Frame* VmStack::currentFrame() const {
    if(_frames.size() ==0)
        return nullptr;
    return _frames.top().get();
}