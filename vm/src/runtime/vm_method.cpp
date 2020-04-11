#include "vm/runtime/vm_method.h"

using namespace avm;

VmMethod::VmMethod(const MethodInfo* method) : _javaMethod(method) {

}

VmMethod::~VmMethod() {

}

u2 VmMethod::getMaxLocals() const {
    return _javaMethod->getCode()->getMaxLocals();
}

u2 VmMethod::getMaxStack() const {
    return _javaMethod->getCode()->getMaxStack();
}

const Instruction* VmMethod::getInstruction(u2 index) const {
    return _javaMethod->getCode()->getInstructionAt(index);
}