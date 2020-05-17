#include "vm/runtime/vm_class.h"

#include <iostream>

using namespace avm;

VmClass::VmClass(std::shared_ptr<JavaClass> javaClass)
    : _javaClass(javaClass),
      _superClass(nullptr),
      _size(0),
      _prepared(false) {
}

VmClass::~VmClass() {

}

const ConstantPool* VmClass::getRuntimeConstantPool() const {
    return _javaClass->getConstantPool();
}

void VmClass::initialize() {
    // todo: <cinit>
}

void VmClass::registerFields() {
    int offset = 0;
    if(_superClass) {
        offset = _superClass->_size;
    }
    int fieldsCount = _javaClass->getFieldsCount();
    for(int i = 0; i < fieldsCount; i++) {
        const FieldInfo* fieldInfo = _javaClass->getFieldAt(i);
        std::unique_ptr<VmField> field;

        if(fieldInfo->isStatic()) {
            /*
             * https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.7.2
            */
            field = VmField::newStaticField(fieldInfo->getName(), fieldInfo->getDescriptor());
            const ConstantValue* constantValue = (ConstantValue*)fieldInfo->getAttrinuteIfPresent(CONSTANT_VALUE);
            if(constantValue != nullptr) {
                u2 index = constantValue->getValueIndex();
                initializeConstantField(*field, index);
            }
        } else {
            // instance fields are located in heap
            field = VmField::newInstanceField(fieldInfo->getName(), fieldInfo->getDescriptor(), offset);
            offset += field->getFieldSize();
        }
        _fields[fieldInfo->getName()] = std::move(field);
    }
    _size = offset;
}

void VmClass::registerMethods() {
    for(int i = 0; i < _javaClass->getMethodsCount(); i++) {
        const MethodInfo* methodInfo = _javaClass->getMethodAt(i);
        std::string methodId = methodInfo->getName() + "<" + methodInfo->getDescriptor() + ">";
        _methods[methodId] = std::unique_ptr<VmMethod>(new VmMethod(methodInfo, this));
    }
}

void VmClass::prepare() {
    if(_prepared)
        return;
    registerFields();
    registerMethods();
    _prepared = true;
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
    const FieldType* fieldType = field.getDescriptor();
    if(fieldType->isBaseType()) {
        switch(((BaseType*)fieldType)->getType()) {
        case FIELD_Byte:
        case FIELD_Short:
        case FIELD_Char:
        case FIELD_Int:
        case FIELD_Boolean: {
            ConstantInteger* c = (ConstantInteger*) info;
            field.setInt(c->getValue());
            break;
        }
        case FIELD_Float: {
            ConstantFloat* c = (ConstantFloat*) info;
            field.setFloat(c->getValue());
            break;
        }
        case FIELD_Long: {
            ConstantLong* c = (ConstantLong*) info;
            field.setLong(c->getValue());
            break;
        }
        case FIELD_Double: {
            ConstantDouble* c = (ConstantDouble*) info;
            field.setDouble(c->getValue());
            break;
        }
        }
    } else if(fieldType->isObject()) {
        ConstantString* c = (ConstantString*) info;
        const std::string* stringRef =  _javaClass->getConstantPool()->getStringReference(c->getStringIndex());
        field.setReference(reinterpret_cast<int64_t>(stringRef));
    } else {
        throw "fixme: support array type";
    }
}