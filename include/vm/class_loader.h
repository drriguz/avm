#ifndef _AVM_CLASS_LOADER_H_
#define _AVM_CLASS_LOADER_H_

#include <string>

#include "format/java_class.h"

namespace avm {

class ClassLoader {
public:
	ClassLoader();
	virtual ~ClassLoader();
public:
	virtual JavaClass loadClass(const std::string& className) = 0;
};
}
#endif
