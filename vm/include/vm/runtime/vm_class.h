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
    VmClass(std::shared_ptr<JavaClass> javaClass);
    virtual ~VmClass();
public:
    const JavaClass* getClass() const {
        return _javaClass.get();
    }
    const ConstantPool* getRuntimeConstantPool() const;
    const VmMethod getClassInitializationMethod() const;

    VmField* getField(const std::string& name) {
        return _fields[name].get();
    }
public:
    void initialize();
protected:
    void prepare();
    void initializeConstantField(VmField& field, u2 constantIndex);
protected:
    int _fieldSlotsCount;
    std::shared_ptr<JavaClass> _javaClass;
    std::map<std::string, std::unique_ptr<VmField>>  _fields;
};
}

#endif