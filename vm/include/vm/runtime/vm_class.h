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
    friend class ClassLoader;
public:
    VmClass(std::shared_ptr<JavaClass> javaClass);
    virtual ~VmClass();
public:
    inline const JavaClass* getRawClass() const {
        return _javaClass.get();
    }
    inline std::string getClassName() const {
        return _javaClass->getClassName();
    }
    inline const VmClass* getSuperClass() const {
        return _superClass.get();
    }
    inline std::vector<std::shared_ptr<VmClass>> getInterfaces() const {
        return _interfaces;
    }
    const ConstantPool* getRuntimeConstantPool() const;
    const VmMethod getClassInitializationMethod() const;
    VmField* getField(const std::string& name) {
        return _fields[name].get();
    }
    inline int getSize() const {
        return _size;
    }
public:
    void initialize();
protected:
    void prepare();
    void initializeConstantField(VmField& field, u2 constantIndex);
protected:
    bool _prepared;
    int _size;
    std::shared_ptr<JavaClass> _javaClass;
    std::shared_ptr<VmClass> _superClass;
    std::vector<std::shared_ptr<VmClass>> _interfaces;
    std::map<std::string, std::unique_ptr<VmField>>  _fields;
    std::map<std::string, std::unique_ptr<VmMethod>> _methods;
};
}

#endif