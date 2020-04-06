#include "vm/virtual_machine.h"
using namespace avm;

VirtualMachine::VirtualMachine(const std::string& classpath,
		const std::string& mainClass)
:_classPath(classpath),
 _mainClass(mainClass),
 _mainThread(nullptr),
 _classLoader(new ClasspathClassLoader(classpath)),
 _methodArea(new MethodArea()){

}

VirtualMachine::~VirtualMachine() {
	delete _classLoader;
	delete _methodArea;
}

void VirtualMachine::execute() {
	const JavaClass* mainClass = getClass(_mainClass);
	const MethodInfo* entry = mainClass->getMethod("main", "([Ljava/lang/String;)V", 2, ACC_PUBLIC, ACC_STATIC);
	if(!entry->isPublic())
		throw MethodNotFoundException("No public main found");

}

const JavaClass* VirtualMachine::getClass(const std::string& className) const{
	if(!_methodArea->loadedClass(className)) {
		JavaClass* newClass = new JavaClass();
		_classLoader->loadClass(className, *newClass);
		_methodArea->putClass(className, newClass);
	}
	return _methodArea->getClass(className);
}