#ifndef _AVM_CLASS_FILE_H_
#define _AVM_CLASS_FILE_H_

#include "types.h"

namespace avm {
class ClassFile {
	friend class ClassParser;

public:
	void verbose();
private:
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
};
}

#endif
