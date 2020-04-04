#ifndef _AVM_CLASS_LOADER_H_
#define _AVM_CLASS_LOADER_H_

#include <string>

#include "class_file/format/java_class.h"

namespace avm {

class ClassLoader {
public:
	ClassLoader();
	virtual ~ClassLoader();
public:
	virtual void loadClass(const std::string& className, JavaClass& out) = 0;
};
}
#endif
