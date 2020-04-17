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
    VmField(const std::string& name, const std::string& descriptor);
    virtual ~VmField();
public:
    void setByte(int8_t value);
    void setShort(int16_t value);
    void setInt(int32_t value);
    void setLong(int64_t value);
    void setFloat(float value);
    void setDouble(double value);
    void setChar(uint16_t value);
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
    int getFieldSlotsSize() const;
protected:
    const FieldInfo* _fieldInfo;
    std::string _name;
    FieldDescriptor _descriptor;
    std::unique_ptr<Slot> _slot1;
    std::unique_ptr<Slot> _slot2;
};
}

#endif