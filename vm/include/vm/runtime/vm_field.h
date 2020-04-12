#ifndef _AVM_VM_FIELD_H_
#define _AVM_VM_FIELD_H_

#include <string>

#include "class_file/format/field_info.h"
#include "slot.h"

namespace avm {
    class VmField {
    public:
        VmField(const std::string& name, const std::string& descriptor);
        virtual ~VmField();
    protected:
        const FieldInfo* _fieldInfo;
        std::string _name;
        std::string _descriptor;
    };
}

#endif