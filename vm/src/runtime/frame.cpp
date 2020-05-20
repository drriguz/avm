#include "vm/runtime/frame.h"

using namespace avm;

Frame::Frame(int locals, int stack, const ConstantPool *constantPool, Frame* previousFrame) :
    _localVariables(locals),
    _operandStack(stack),
    _runtimeConstants(constantPool),
    _pc(0),
    _previousFrame(previousFrame) {
}

Frame::~Frame() {

}

void Frame::dump() const {
    _localVariables.dump();
    _operandStack.dump();
}