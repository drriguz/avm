#ifndef _AVM_JAVA_VM_H_
#define _AVM_JAVA_VM_H_

#include <string>

#include "class_loader.h"
#include "classpath_class_loader.h"
#include "method_area.h"

namespace avm {

class VirtualMachine {
public:
	VirtualMachine(const std::string& classpath, const std::string& mainClass);
	virtual ~VirtualMachine();
public:
	void execute();
protected:
	const JavaClass* getClass(const std::string& className) const;
protected:
	std::string _classPath;
	std::string _mainClass;
	ClassLoader* _classLoader;
	MethodArea* _methodArea;
};
}

#endif
