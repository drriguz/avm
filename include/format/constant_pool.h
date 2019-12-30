#ifndef _AVM_CONSTANT_POOL_H_
#define _AVM_CONSTANT_POOL_H_

#include "types.h"
#include "constants/constant_types.h"

namespace avm {
enum ConstantType {
	Class = 7,
	Fieldref = 9,
	Methodref = 10,
	InterfaceMethodref = 11,
	String = 8,
	Integer = 3,
	Float = 4,
	Long = 5,
	Double = 6,
	NameAndType = 12,
	Utf8 = 1,
	MethodHandle = 15,
	MethodType = 16,
	InvokeDynamic = 18,
};

struct ConstantInfo {
	ConstantType _type;
	u1 * _info;
};
}

#endif
