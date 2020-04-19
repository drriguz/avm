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
    bool isLoaded(const std::string &className) const;
    std::shared_ptr<VmClass> getClass(const std::string &className) const;
    void registerClass(const std::string &className, std::shared_ptr<VmClass> javaClass);
protected:
    std::map<std::string, std::shared_ptr<VmClass>> _loadedClasses;
};

}

#endif
