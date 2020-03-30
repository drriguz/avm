#include "vm/virtual_machine.h"
using namespace avm;

VirtualMachine::VirtualMachine(const std::string& classpath,
		const std::string& mainClass)
:_classPath(classpath),
 _mainClass(mainClass),
 _classLoader(new ClasspathClassLoader(classpath)),
 _methodArea(new MethodArea()){

}

VirtualMachine::~VirtualMachine() {
	delete _classLoader;
	delete _methodArea;
}

void VirtualMachine::execute() {

}
