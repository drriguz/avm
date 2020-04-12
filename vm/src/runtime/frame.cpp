#include "vm/runtime/frame.h"

using namespace avm;

Frame::Frame(int locals, int stack, const ConstantPool *constantPool) :
        _localVariables(locals),
        _operandStack(stack),
        _runtimeConstants(constantPool),
        _returned(false) {
}

Frame::~Frame() {

}

void Frame::returnVoid() {
        _returned = true;
}