#include "vm/runtime/vm_method.h"

#include <iostream>

using namespace avm;

VmMethod::VmMethod(const MethodInfo* method, const VmClass* methodClass)
    : _javaMethod(method),
      _class(methodClass),
      _name(method->getName()),
      _descriptor(method->getDescriptor()),
      _isNative(method->isNative()) {
    // int begin = _descriptor.find_first_of("("), end = _descriptor.find_first_of(")");
    // std::string parameters = _descriptor.substr(begin + 1, end - begin -1);
    // std::cout<< _descriptor << " => " << parameters << std::endl;
    // for(int i = 0; i < parameters.length(); i++) {
    //     char t = parameters.at(t);

    // }
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