#ifndef _AVM_DESCRIPTOR_TYPE_H_
#define _AVM_DESCRIPTOR_TYPE_H_

#include <string>

namespace avm {
enum BaseType {
    FIELD_Byte,
    FIELD_Char,
    FIELD_Double,
    FIELD_Float,
    FIELD_Int,
    FIELD_Long,
    FIELD_Short,
    FIELD_Boolean,
    FIELD_Reference,
};
class FieldDescriptor {
public:
    FieldDescriptor(const std::string& descriptor);
    virtual ~FieldDescriptor();
public:
    inline BaseType getBaseType() const {
        return _baseType;
    }
    inline std::string getClassName() const {
        return _className;
    }
    inline bool isArray() const {
        return _isArray;
    }
    inline bool isDoubleBytes() const {
        // it's 64bit address size under x64
        return _baseType == FIELD_Long || _baseType == FIELD_Double || _baseType == FIELD_Reference;
    }
protected:
    BaseType _baseType;
    std::string _className;
    bool _isArray;
};
}

#endif