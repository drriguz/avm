#include "vm/virtual_machine.h"
#include "vm/runtime/vm_method.h"
#include "vm/interpreter.h"

using namespace avm;

VirtualMachine::VirtualMachine(const std::string &classpath,
                               const std::string &mainClass) :
    _classPath(classpath),
    _mainClass(mainClass),
    _mainThread(nullptr),
    _classLoader(std::unique_ptr<ClassLoader>(new ClasspathClassLoader(classpath))),
    _methodArea(std::unique_ptr<MethodArea>(new MethodArea())) {

}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::execute() {
    VmClass *mainClass = getClass(_mainClass);
    const MethodInfo* entry = mainClass->getClass()->getMethod("main",
                              "([Ljava/lang/String;)V", 2, ACC_PUBLIC, ACC_STATIC);
    VmMethod method(entry);
    _mainThread = std::unique_ptr<VmThread>(new VmThread(mainClass, &method));
    execute(_mainThread.get());
}

void VirtualMachine::execute(VmThread* thread) {
    Interpreter interpreter;
    Context context(this, thread);
    interpreter.execute(context);
}

VmClass* VirtualMachine::getClass(const std::string &className) const {
    if (!_methodArea->loadedClass(className)) {
        auto newClass = std::unique_ptr<JavaClass>(new JavaClass());
        _classLoader->loadClass(className, *newClass.get());
        auto vmClass = std::unique_ptr<VmClass>(new VmClass(std::move(newClass)));
        _methodArea->putClass(className, std::move(vmClass));
    }
    return _methodArea->getClass(className);
}
