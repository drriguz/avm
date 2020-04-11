#ifndef _AVM_VM_CLASS_H_
#define _AVM_VM_CLASS_H_

#include <map>
#include <string>

#include "class_file/format/java_class.h"
#include "vm_method.h"

namespace avm {

class VmClass {
public:
    VmClass(const JavaClass* javaClass) : _javaClass(javaClass) {

    }
    virtual ~VmClass();
protected:
    const JavaClass* _javaClass;
};
}

#endif