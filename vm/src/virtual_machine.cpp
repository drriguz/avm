#include "vm/virtual_machine.h"
#include "vm/runtime/vm_method.h"
#include "vm/interpreter.h"

using namespace avm;

VirtualMachine::VirtualMachine(const std::string &classpath,
                               const std::string &mainClass) :
    _classPath(classpath),
    _mainClass(mainClass),
    _mainThread(nullptr),
    _heap(std::unique_ptr<Heap>(new Heap(1* 1024 * 1024 * 10))), // aka 10Mb
    _methodArea(std::unique_ptr<MethodArea>(new MethodArea())) {
    _classLoader =std::unique_ptr<ClassLoader>(new ClasspathClassLoader(classpath));
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::execute() {
    VmClass *mainClass = getClass(_mainClass);
    const MethodInfo* entry = mainClass->getRawClass()->getMethod("main",
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
    if ( !_methodArea->isLoaded(className)) {
        _classLoader->load(className, _methodArea.get());
    }
    return _methodArea->getClass(className).get();
}
