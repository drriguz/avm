#ifndef _AVM_CLASS_LOADER_H_
#define _AVM_CLASS_LOADER_H_

#include <string>
#include <map>

#include "class_file/format/java_class.h"
#include "runtime/method_area.h"
#include "runtime/vm_class.h"

namespace avm {

class ClassLoader {
public:
    ClassLoader(MethodArea* methodArea);
    virtual ~ClassLoader();
public:
    void load(const std::string& className);
protected:
    virtual void readClass(const std::string &className, JavaClass &out) = 0;
    void defineClass(const JavaClass& theClass);
    void link(const JavaClass& theClass);
protected:
    MethodArea* _methodArea;
    std::map<std::string, std::shared_ptr<JavaClass>> _loadedClasses;
};
}
#endif
