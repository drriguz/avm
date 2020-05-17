#include "vm/runtime/frame.h"

using namespace avm;

Frame::Frame(int locals, int stack, const ConstantPool *constantPool, Frame* previousFrame) :
    _localVariables(locals),
    _operandStack(stack),
    _runtimeConstants(constantPool),
    _pcOffset(0),
    _returned(false),
    _previousFrame(previousFrame) {
}

Frame::~Frame() {

}

void Frame::returnVoid() {
    _returned = true;
}

void Frame::dump() const {
    _localVariables.dump();
    _operandStack.dump();
}