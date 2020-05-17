#ifndef _AVM_DESCRIPTOR_TYPE_H_
#define _AVM_DESCRIPTOR_TYPE_H_

#include <string>
#include <vector>
#include <memory>

namespace avm {
enum BaseFieldType {
    FIELD_Byte,
    FIELD_Char,
    FIELD_Double,
    FIELD_Float,
    FIELD_Int,
    FIELD_Long,
    FIELD_Short,
    FIELD_Boolean,
};

class FieldType {
public:
    inline virtual bool isBaseType() const {
        return false;
    }
    inline virtual bool isArray() const {
        return false;
    }
    inline virtual bool isObject() const {
        return false;
    }
    virtual bool isDoubleBytes() const {
        return false;
    }
public:
    static std::unique_ptr<FieldType> fromFieldDescriptor(
        const std::string& fieldDescriptor);
    static std::vector<std::unique_ptr<FieldType>> fromSignature(
        const std::string& methodSignature);
private:
    static std::unique_ptr<FieldType> fromFieldDescriptor(
        const std::string& fieldDescriptor, int startPos, int& endPos);
};

class BaseType: public FieldType {
public:
    BaseType(char type);
    BaseType(const BaseFieldType& type);
public:
    inline virtual bool isBaseType() const {
        return true;
    }
    inline BaseFieldType getType() const {
        return _type;
    }
    inline virtual bool isDoubleBytes() const {
        return _type == FIELD_Long || _type == FIELD_Double;
    }
protected:
    BaseFieldType _type;
};

class ObjectType: public FieldType {
public:
    ObjectType(const std::string& className);
public:
    inline virtual bool isObject() const {
        return true;
    }
    inline std::string getClassName() const {
        return _className;
    }
    inline virtual bool isDoubleBytes() const {
#ifdef _ARCH_X64_
        return true;
#else
        return false;
#endif
    }
protected:
    std::string _className;
};

class ArrayType: public FieldType {
public:
    ArrayType(std::unique_ptr<FieldType> componentType);
public:
    inline virtual bool isArray() const{
        return true;
    }
    virtual bool isDoubleBytes() const {
#ifdef _ARCH_X64_
        return true;
#else
        return false;
#endif
    }
    const FieldType* getComponentType() const {
        return _componentType.get();
    }
protected:
    std::unique_ptr<FieldType> _componentType;
};

}

#endif