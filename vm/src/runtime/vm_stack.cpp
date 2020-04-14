#include "vm/runtime/vm_stack.h"

using namespace avm;

VmStack::VmStack() {

}

VmStack::~VmStack() {

}

void VmStack::push(Frame* frame) {
    _frames.push(std::unique_ptr<Frame>(frame));
}
void VmStack::pop() {
    _frames.pop();
}
Frame* VmStack::currentFrame() {
    return _frames.top().get();
}