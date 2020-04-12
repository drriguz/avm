#ifndef _AVM_VM_CLASS_H_
#define _AVM_VM_CLASS_H_

#include <map>
#include <string>
#include <memory>

#include "class_file/format/java_class.h"
#include "vm_method.h"
#include "vm_field.h"

namespace avm {

class VmClass {
public:
    VmClass(const JavaClass* javaClass);
    virtual ~VmClass();
public:
    const ConstantPool* getRuntimeConstantPool() const;
    const VmMethod getClassInitializationMethod() const;
    void prepare();
protected:
    const JavaClass* _javaClass;
    std::map<std::string, std::unique_ptr<VmField>>  _fields;
};
}

#endif