#include "class_file/format/descriptor_type.h"
#include "vm/exceptions.h"

using namespace avm;

BaseType detectPrimitiveType(const std::string& descriptor) {
    if(descriptor == "B")
        return Byte;
    else if(descriptor == "C")
        return Char;
    else if(descriptor == "D")
        return Double;
    else if(descriptor == "F")
        return Float;
    else if(descriptor == "I")
        return Int;
    else if(descriptor == "J")
        return Long;
    else if(descriptor == "S")
        return Short;
    else if(descriptor == "Z")
        return Boolean;
    else
        throw RuntimeException("Descriptor not recognized");
}
FieldDescriptor::FieldDescriptor(const std::string& descriptor) {
    std::string componentType = descriptor;
    if(descriptor.rfind("[", 0) == 0) {
        componentType = descriptor.substr(1);
        _isArray = true;
    }

    if(componentType.rfind("L", 0) == 0) {
        _baseType = Reference;
        _className = componentType.substr(1);
    } else
        _baseType = detectPrimitiveType(componentType);
}

FieldDescriptor::~FieldDescriptor() {

}