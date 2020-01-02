#include "vm/jvm.h"
using namespace avm;

VirtualMachine::VirtualMachine(const std::string& classpath,
		const std::string& mainClass)
:_classPath(classpath), _mainClass(mainClass){

}

VirtualMachine::~VirtualMachine() {

}

void VirtualMachine::execute() {

}
