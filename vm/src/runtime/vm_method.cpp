#include "vm/runtime/vm_method.h"

using namespace avm;

VmMethod::VmMethod(const MethodInfo* method)
    : _javaMethod(method), 
    _name(method->getName()), 
    _descriptor(method->getDescriptor()), 
    _isNative(method->isNative()) {
}

VmMethod::~VmMethod() {

}

u2 VmMethod::getMaxLocals() const {
    if(_isNative)
        return 0;
    return _javaMethod->getCode()->getMaxLocals();
}

u2 VmMethod::getMaxStack() const {
    if(_isNative)
        return 0;
    return _javaMethod->getCode()->getMaxStack();
}

const Instruction* VmMethod::getInstruction(u2 index) const {
    if(_isNative)
        return nullptr;
    return _javaMethod->getCode()->getInstructionAt(index);
}

u2 VmMethod:: getInstructionsCount() const {
    if(_isNative)
        return 0;
    return _javaMethod->getCode()->getInstructionsCount();
}