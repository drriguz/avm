#ifndef _AVM_SHARED_CONSTANT_TYPES_H_
#define _AVM_SHARED_CONSTANT_TYPES_H_

#include "../types.h"

namespace avm {

class SingleReference {
public:
	SingleReference(const u2& index);
protected:
	u2 _index;
};

class ClassPropertyRef {
public:
	ClassPropertyRef(const u2& classIndex, const u2& nameAndTypeIndex);
public:
	inline const u2 getClassIndex() const { return _classIndex; }
	inline const u2 getNameAndTypeIndex() const { return _nameAndTypeIndex; }
protected:
	u2 _classIndex;
	u2 _nameAndTypeIndex;
};

class SinglePrecisionNumber {
public:
	SinglePrecisionNumber(const u4& bytes);
public:
	inline const u4 getBytes() const { return _bytes; }
protected:
	u4 _bytes;
};

class DoublePrecisionNumber {
public:
	DoublePrecisionNumber(const u4& highBytes, const u4& lowBytes);
public:
	inline const u4 getHighBytes() const { return _highBytes; }
	inline const u4 getLowBytes() const { return _lowBytes; }
protected:
	u4 _highBytes;
	u4 _lowBytes;
};


}

#endif
