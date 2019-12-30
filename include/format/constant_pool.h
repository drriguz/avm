#ifndef _AVM_CONSTANT_POOL_H_
#define _AVM_CONSTANT_POOL_H_

#include "types.h"

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
	ConstantType type;
	u1 * info;
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

struct ConstantUtf8 {
	ConstantUtf8() : length(0), bytes(nullptr) {
	}
	~ConstantUtf8() {
		if (bytes)
			delete[] bytes;
	}
	void initializeStringBuffer() {
		if (bytes)
			delete[] bytes;
		bytes = new u1[length + 1];
	}
	u2 length;
	u1 *bytes;
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
