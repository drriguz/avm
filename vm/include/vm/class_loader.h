#ifndef _AVM_CLASS_LOADER_H_
#define _AVM_CLASS_LOADER_H_

#include <string>
#include <map>

#include "class_file/format/java_class.h"
#include "runtime/vm_class.h"
#include "runtime/method_area.h"

namespace avm {

class ClassLoader {
public:
    ClassLoader();
    virtual ~ClassLoader();
public:
    std::shared_ptr<VmClass> load(const std::string& className, MethodArea* methodArea);
protected:
    virtual void readClass(const std::string &className, JavaClass &out) = 0;
    std::shared_ptr<JavaClass> readClass(const std::string &className);
    void defineClass();
    void link(VmClass* vmClass);
protected:
    std::map<std::string, std::shared_ptr<JavaClass>> _classCache;
};
}
#endif
