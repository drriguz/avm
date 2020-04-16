#ifndef _AVM_JAVA_VM_H_
#define _AVM_JAVA_VM_H_

#include <string>
#include <memory>

#include "class_loader.h"
#include "classpath_class_loader.h"
#include "runtime/method_area.h"
#include "runtime/vm_thread.h"

namespace avm {

class VirtualMachine {
public:
    VirtualMachine(const std::string &classpath, const std::string &mainClass);
    virtual ~VirtualMachine();
public:
    void execute();
    void execute(VmThread* thread);
    VmClass* getClass(const std::string &className) const;
protected:
    std::string _classPath;
    std::string _mainClass;
    std::unique_ptr<ClassLoader> _classLoader;
    std::unique_ptr<MethodArea> _methodArea;
    std::unique_ptr<VmThread> _mainThread;
};
}

#endif
