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
            /*
             * https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.7.2
            */
            const ConstantValue* constantValue = (ConstantValue*)fieldInfo->getAttrinuteIfPresent(CONSTANT_VALUE);
            if(constantValue != nullptr) {
                u2 index = constantValue->getValueIndex();

            }
        }
    }
}

/*
    Field Type 	Entry Type
    long 	                             CONSTANT_Long
    float 	                             CONSTANT_Float
    double 	                             CONSTANT_Double
    int, short, char, byte, boolean 	 CONSTANT_Integer
    String 	                             CONSTANT_String
*/
void VmClass::initializeConstantField(VmField& field, u2 constantIndex) {
    const ConstantInfo* info = _javaClass->getConstantPool()->at(constantIndex);
    std::string fieldType = field.getDescriptor();
}