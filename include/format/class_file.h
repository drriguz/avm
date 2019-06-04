#ifndef _AVM_CLASS_FILE_H_
#define _AVM_CLASS_FILE_H_

#include "types.h"
#include "constants.h"

namespace avm {
class ClassFile {
	friend class ClassParser;
public:
	ClassFile();
	virtual ~ClassFile();
public:
	void verbose();
private:
	void ensureConstantPool();
	void ensureInterfaces();
	void printConstantPool();
	void printInterfaces();
private:
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	ConstantInfo* constant_pool;
	u2 access_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2* interfaces;
};
}

#endif
