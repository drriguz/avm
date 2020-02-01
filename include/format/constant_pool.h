#ifndef _AVM_CONSTANT_POOL_H_
#define _AVM_CONSTANT_POOL_H_

#include "types.h"
#include "constant/constant_types.h"
#include "constant/constant_info.h"
#include "constant/utf8.h"

namespace avm {


class CClass: public Constant {
public:
	CClass(const u2& nameIndex);
private:
	const u2 _nameIndex;
};

struct ConstantClass {
	u2 nameIndex;
};

struct ConstantFieldref {
	u2 classIndex;
	u2 nameAndTypeIndex;
};

struct ConstantMethodref {
	u2 classIndex;
	u2 nameAndTypeIndex;
};

struct ConstantInterfaceMethodref {
	u2 classIndex;
	u2 nameAndTypeIndex;
};

struct ConstantString {
	u2 stringIndex;
};

struct ConstantInteger {
	u4 bytes;
};

struct ConstantFloat {
	mutable u4 bytes;
	float &getValue() const {
		return *reinterpret_cast<float *>(&bytes);
	}
};

struct ConstantLong {
	mutable u4 highBytes;
	mutable u4 lowBytes;
	long getValue() const {
		return ((long)highBytes << 32) + lowBytes;
	}
};

struct ConstantDouble {
	mutable u4 highBytes;
	mutable u4 lowBytes;
	double getValue() const {
		long value = ((long)highBytes << 32) + lowBytes;
		return *reinterpret_cast<double *>(&value);
	}
};

struct ConstantNameAndType {
	u2 nameIndex;
	u2 descriptorIndex;
};

struct ConstantMethodHandle {
	u1 tag;
	u1 referenceKind;
	u2 referenceIndex;
};

struct ConstantMethodType {
	u1 tag;
	u2 descriptorIndex;
};

struct ConstantInvokeDynamic {
	u1 tag;
	u2 bootstrapMethodAttrIndex;
	u2 nameAndTypeIndex;
};
}

#endif
