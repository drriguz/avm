#ifndef _AVM_CLASS_LOADER_H_
#define _AVM_CLASS_LOADER_H_

#include <string>
#include <map>

#include "class_file/format/java_class.h"
#include "runtime/vm_class.h"

namespace avm {

class ClassLoader {
public:
    ClassLoader();
    virtual ~ClassLoader();
public:
    std::unique_ptr<VmClass> load(const std::string& className);
protected:
    virtual void readClass(const std::string &className, JavaClass &out) = 0;
    std::shared_ptr<JavaClass> readClass(const std::string &className);
    void defineClass(const JavaClass& theClass);
    void link(const JavaClass& theClass);
protected:
    std::map<std::string, std::shared_ptr<JavaClass>> _classCache;
};
}
#endif
