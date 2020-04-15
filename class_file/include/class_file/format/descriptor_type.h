#ifndef _AVM_DESCRIPTOR_TYPE_H_
#define _AVM_DESCRIPTOR_TYPE_H_

#include <string>

namespace avm {
enum BaseType {
    Byte,
    Char,
    Double,
    Float,
    Int,
    Long,
    Short,
    Boolean,
    Reference,
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

protected:
    BaseType _baseType;
    std::string _className;
    bool _isArray;
};
}

#endif