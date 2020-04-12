#include "vm/virtual_machine.h"
#include "vm/runtime/vm_method.h"
#include "vm/interpreter.h"

using namespace avm;

VirtualMachine::VirtualMachine(const std::string &classpath,
                               const std::string &mainClass) :
        _classPath(classpath),
        _mainClass(mainClass),
        _mainThread(nullptr),
        _classLoader(new ClasspathClassLoader(classpath)),
        _methodArea(new MethodArea()) {

}

VirtualMachine::~VirtualMachine() {
    delete _classLoader;
    delete _methodArea;
    if(_mainThread)
        delete _mainThread;
}

void VirtualMachine::execute() {
    const JavaClass *mainClass = getClass(_mainClass);
    const MethodInfo *entry = mainClass->getMethod("main",
            "([Ljava/lang/String;)V", 2, ACC_PUBLIC, ACC_STATIC);
    VmClass entryClass(mainClass);
    VmMethod entryMethod(entry);
    _mainThread = new VmThread(&entryClass, &entryMethod);
    execute(_mainThread);
}

void VirtualMachine::execute(VmThread* thread) {
    Interpreter interpreter;
    Context context(this, thread);
    interpreter.execute(context);
}

const JavaClass* VirtualMachine::getClass(const std::string &className) const {
    if (!_methodArea->loadedClass(className)) {
        JavaClass *newClass = new JavaClass();
        _classLoader->loadClass(className, *newClass);
        _methodArea->putClass(className, newClass);
    }
    return _methodArea->getClass(className);
}
