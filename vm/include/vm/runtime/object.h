#ifndef _AVM_OBJECT_H_
#define _AVM_OBJECT_H_

#include <map>
#include <string>
#include <cstdint>

#include "class_file/format/java_class.h"

namespace avm {

class Object {
protected:
	JavaClass* _class;
	std::map<std::string, uint32_t> _fieldReferences;
};
}
#endif
