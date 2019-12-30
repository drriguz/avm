#ifndef _AVM_CONSTANT_TYPES_H_
#define _AVM_CONSTANT_TYPES_H_

#include "shared_constant_types.h"

namespace avm {

class ConstantClass: public SingleReference {
public:
	ConstantClass(const u2& classIndex);
public:
	inline const u2 getClassIndex() const{ return _index; }
};

class ConstantFieldref: public ClassPropertyRef{
public:
	ConstantFieldref(const u2& classIndex, const u2& nameAndTypeIndex);
};

class ConstantMethodref: public ClassPropertyRef{
public:
	ConstantMethodref(const u2& classIndex, const u2& nameAndTypeIndex);
};

class ConstantInterfaceMethodref: public ClassPropertyRef{
public:
	ConstantInterfaceMethodref(const u2& classIndex, const u2& nameAndTypeIndex);
};

class ConstantString: public SingleReference {
public:
	ConstantString(const u2& stringIndex);
public:
	inline const u2 getStringIndex() const{ return _index; }
};

class ConstantInteger: public SinglePrecisionNumber {
public:
	ConstantInteger(const u4& bytes);
};

class ConstantFloat: public SinglePrecisionNumber {
public:
	ConstantFloat(const u4& bytes);
};

class ConstantLong: public DoublePrecisionNumber {
public:
	ConstantLong(const u4& highBytes, const u4& lowBytes);
};

class ConstantDouble: public DoublePrecisionNumber {
public:
	ConstantDouble(const u4& highBytes, const u4& lowBytes);
};

class ConstantNameAndType {
public:
	ConstantNameAndType(const u2& nameIndex, const u2& descriptorIndex);
protected:
	u2 _nameIndex;
	u2 _descriptorIndex;
};

class ConstantUtf8 {
public:
	ConstantUtf8(const u2& length, const u1* bytes);
protected:
	u2 _length;
	u1* _bytes;
};

class ConstantMethodHandle {
public:
	ConstantMethodHandle(const u1& referenceKind, const u2& referenceIndex);
protected:
	u1 _referenceKind;
	u2 _referenceIndex;
};

class ConstantMethodType {
public:
	ConstantMethodType(const u2& descriptorIndex);
protected:
	u2 _descriptorIndex;
};

class ConstantInvokeDynamic {
public:
	ConstantInvokeDynamic(const u2& bootstrapMethodAttrIndex, const u2& nameAndTypeIndex);
protected:
	u1 _bootstrapMethodAttrIndex;
	u2 _nameAndTypeIndex;
};
}

#endif
