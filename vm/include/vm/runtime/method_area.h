#ifndef _AVM_METHOD_AREA_H_
#define _AVM_METHOD_AREA_H_

#include <map>
#include <string>
#include <memory>

#include "class_file/format/java_class.h"
#include "vm_class.h"

namespace avm {

class MethodArea {
public:
    MethodArea();
    virtual ~MethodArea();
public:
    bool loadedClass(const std::string &className) const;
    VmClass* getClass(const std::string &className) const;
    void putClass(const std::string &className, std::unique_ptr<VmClass> javaClass);
protected:
    std::map<std::string, std::unique_ptr<VmClass>> _loadedClasses;
};

}

#endif
