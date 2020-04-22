#ifndef _AVM_VM_FIELD_H_
#define _AVM_VM_FIELD_H_

#include <string>
#include <vector>
#include <memory>

#include "class_file/format/field_info.h"
#include "class_file/format/descriptor_type.h"
#include "slot.h"

namespace avm {
class VmField {
public:
    VmField(const std::string& name, const FieldDescriptor& descriptor, const int slotId, const bool isStatic, uint32_t value1, uint32_t value2);
    virtual ~VmField();
    static std::unique_ptr<VmField> newStaticField(const std::string& name, const std::string& descriptor);
    static std::unique_ptr<VmField> newInstanceField(const std::string& name, const std::string& descriptor, const int fieldId);
public:
    void setByte(int8_t value);
    void setShort(int16_t value);
    void setInt(int32_t value);
    void setLong(int64_t value);
    void setFloat(float value);
    void setDouble(double value);
    void setChar(uint16_t value);
    void setReference(reference value);
public:
    int8_t getByte() const;
    int16_t getShort() const;
    int32_t getInt() const;
    int64_t getLong() const;
    float getFloat() const;
    double getDouble() const;
    uint16_t getChar() const;
    std::string getString() const;
public:
    inline std::string getName() const {
        return _name;
    }
    inline FieldDescriptor getDescriptor() const {
        return _descriptor;
    }
    inline int getOffset() const {
        return _offset;
    }
    int getFieldSize() const;
protected:
    int _offset;
    bool _isStatic;
    const FieldInfo* _fieldInfo;
    std::string _name;
    FieldDescriptor _descriptor;
    uint32_t _value1;
    uint32_t _value2;
};
}

#endif