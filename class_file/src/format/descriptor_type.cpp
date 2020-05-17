#include "class_file/format/descriptor_type.h"
#include "vm/exceptions.h"

using namespace avm;

BaseType::BaseType(char type) {
    if(type == 'B')
        _type = FIELD_Byte;
    else if(type == 'C')
        _type =  FIELD_Char;
    else if(type == 'D')
        _type =  FIELD_Double;
    else if(type == 'F')
        _type =  FIELD_Float;
    else if(type == 'I')
        _type =  FIELD_Int;
    else if(type == 'J')
        _type =  FIELD_Long;
    else if(type == 'S')
        _type =  FIELD_Short;
    else if(type == 'Z')
        _type =  FIELD_Boolean;
    else
        throw RuntimeException("Descriptor not recognized");
}
BaseType::BaseType(const BaseFieldType& type)
    :_type(type) {

}
ObjectType::ObjectType(const std::string& className)
    :_className(className) {

}

ArrayType::ArrayType(std::unique_ptr<FieldType> componentType)
    :_componentType(std::move(componentType)) {

}
const std::string baseTypes = "BCDFIJSZ";
std::unique_ptr<FieldType> FieldType::fromFieldDescriptor(const std::string& fieldDescriptor) {
    int endPos = 0;
    return fromFieldDescriptor(fieldDescriptor, 0, endPos);
}

std::unique_ptr<FieldType> FieldType::fromFieldDescriptor(const std::string& fieldDescriptor, int startPos, int& endPos) {
    char t = fieldDescriptor.at(startPos);
    if(baseTypes.find(t) != std::string::npos) {
        endPos = startPos;
        return std::unique_ptr<FieldType>(new BaseType(t));
    } else if(t == 'L') {
        // L ClassName ;
        endPos = fieldDescriptor.find_first_of(';');
        if(endPos == std::string::npos)
            throw RuntimeException("Descriptor not recognized: class name not ended");
        std::string className = fieldDescriptor.substr(startPos + 1, endPos);
        return std::unique_ptr<FieldType>(new ObjectType(className));
    } else if (t == '[') {
        std::unique_ptr<FieldType> componentType = fromFieldDescriptor(fieldDescriptor, startPos + 1, endPos);
        return std::unique_ptr<FieldType>(new ArrayType(std::move(componentType)));
    } else
        throw RuntimeException("Descriptor not recognized: Unknown");
}

std::vector<std::unique_ptr<FieldType>> FieldType::fromSignature(const std::string& methodSignature) {
    // (II)I
    std::string parameterTypes = methodSignature.substr(1, methodSignature.find_first_of(')') - 1);
    int i = 0;
    std::vector<std::unique_ptr<FieldType>> types;
    do {
        std::unique_ptr<FieldType> paramType = fromFieldDescriptor(parameterTypes, i + 1, i);
        types.push_back(std::move(paramType));
    } while(i < parameterTypes.size() -1);
    return types;
}