#include "class_file/format/descriptor_type.h"
#include "vm/exceptions.h"
#include <iostream>

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

DescriptorParser::DescriptorParser(const std::string& signature)
    :_signature(signature),
     _currentPos(0) {

}
const std::string baseTypes = "BCDFIJSZ";

std::unique_ptr<FieldType> DescriptorParser::nextField() {

    if(_currentPos >= _signature.length())
        return nullptr;
    char t = _signature.at(_currentPos);
    std::cout << "-> " << _currentPos << " " << t << std::endl;
    if(baseTypes.find(t) != std::string::npos) {
        _currentPos++;
        return std::unique_ptr<FieldType>(new BaseType(t));
    } else if(t == 'L') {
        // L ClassName ;
        int end = _signature.find(';', _currentPos + 1);
        if(end == std::string::npos)
            throw RuntimeException("Descriptor not recognized: class name not ended");
        std::string className = _signature.substr(_currentPos + 1, end);
        _currentPos = end + 1;
        return std::unique_ptr<FieldType>(new ObjectType(className));
    } else if (t == '[') {
        _currentPos++;
        std::unique_ptr<FieldType> componentType = nextField();
        if(componentType == nullptr)
            throw RuntimeException("Array type not found");
        return std::unique_ptr<FieldType>(new ArrayType(std::move(componentType)));
    } else
        throw RuntimeException("Descriptor not recognized: Unknown");
}

std::unique_ptr<FieldType> FieldType::fromFieldDescriptor(const std::string& fieldDescriptor) {
    DescriptorParser parser(fieldDescriptor);

    auto type = std::move(parser.nextField());
    if(type == nullptr)
        throw RuntimeException("Unable to get field type");
    return std::move(type);
}

std::vector<std::unique_ptr<FieldType>> FieldType::fromSignature(const std::string& methodSignature) {
    // (II)I
    std::string parameterTypes = methodSignature.substr(1, methodSignature.find_first_of(')') - 1);
    DescriptorParser parser(parameterTypes);
    std::vector<std::unique_ptr<FieldType>> types;
    std::unique_ptr<FieldType> type;
    while((type = parser.nextField()) != nullptr)
        types.push_back(std::move(type));

    return types;
}