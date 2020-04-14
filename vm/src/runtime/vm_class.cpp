#include "vm/runtime/vm_class.h"

using namespace avm;

VmClass::VmClass(JavaClass* javaClass) : _javaClass(javaClass) {
    prepare();
}

VmClass::~VmClass() {

}

const ConstantPool* VmClass::getRuntimeConstantPool() const {
    return _javaClass->getConstantPool();
}

const VmMethod VmClass::getClassInitializationMethod() const {
    try {
        const MethodInfo* cinit = _javaClass->getMethod("<cinit>", "()V");
        return VmMethod(cinit);
    } catch(MethodNotFoundException) {
        return nullptr;
    }
}

void VmClass::prepare() {
    int fieldsCount = _javaClass->getFieldsCount();
    for(int i = 0; i < fieldsCount; i++) {
        const FieldInfo* fieldInfo = _javaClass->getFieldAt(i);
        VmField* field = new VmField(fieldInfo->getName(), fieldInfo->getDescriptor());
        _fields[fieldInfo->getName()] = std::unique_ptr<VmField>(field);
        if(fieldInfo->isStatic()) {
            const ConstantValue* constantValue = (ConstantValue*)fieldInfo->getAttrinuteIfPresent(CONSTANT_VALUE);
            if(constantValue != nullptr) {
                u2 index = constantValue->getValueIndex();
            }
        }
    }
}