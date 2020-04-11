#include "vm/runtime/vm_class.h"

using namespace avm;

VmClass::VmClass(const JavaClass* javaClass) : _javaClass(javaClass) {

}

VmClass::~VmClass() {

}

const ConstantPool* VmClass::getRuntimeConstantPool() const {
    return _javaClass->getConstantPool();
}