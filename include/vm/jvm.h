#ifndef _AVM_JAVA_VM_H_
#define _AVM_JAVA_VM_H_

#include <string>

namespace avm {

class VirtualMachine {
public:
	VirtualMachine(const std::string& classpath, const std::string& mainClass);
	virtual ~VirtualMachine();
public:
	void execute();
protected:
	std::string _classPath;
	std::string _mainClass;
};
}

#endif
