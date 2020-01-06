#ifndef _AVM_METHOD_AREA_H_
#define _AVM_METHOD_AREA_H_

#include <map>
#include <string>

#include "format/java_class.h"

namespace avm {

class MethodArea {
public:
	MethodArea();
	virtual ~MethodArea();
public:
	const JavaClass& getClass(const std::string& className) const;
	void putClass(const std::string& className, const JavaClass& javaClass);
protected:
	std::map<std::string, JavaClass> _classes;
};

}

#endif
