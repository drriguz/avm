#include "class_file/format/descriptor_type.h"
#include "vm/exceptions.h"

using namespace avm;

BaseType detectPrimitiveType(const std::string& descriptor) {
    if(descriptor == "B")
        return FIELD_Byte;
    else if(descriptor == "C")
        return FIELD_Char;
    else if(descriptor == "D")
        return FIELD_Double;
    else if(descriptor == "F")
        return FIELD_Float;
    else if(descriptor == "I")
        return FIELD_Int;
    else if(descriptor == "J")
        return FIELD_Long;
    else if(descriptor == "S")
        return FIELD_Short;
    else if(descriptor == "Z")
        return FIELD_Boolean;
    else
        throw RuntimeException("Descriptor not recognized");
}
FieldDescriptor::FieldDescriptor(const std::string& descriptor) {
    std::string componentType = descriptor;
    if(descriptor.rfind("[", 0) == 0) {
        // fixme: support [[I (int[][])
        componentType = descriptor.substr(1);
        _isArray = true;
    }

    if(componentType.rfind("L", 0) == 0) {
        _baseType = FIELD_Reference;
        _className = componentType.substr(1);
    } else
        _baseType = detectPrimitiveType(componentType);
}

FieldDescriptor::~FieldDescriptor() {

}