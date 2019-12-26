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

class ConstantInfo {
private:
	ConstantType _type;
	u1 *info;
};

/*
 * CONSTANT_Class_info
 * CONSTANT_String_info
 */
class _ConstantReference {
public:
	_ConstantReference(u2 index) :_index(index){};
protected:
	u2 _index;
};

class ConstantClass: public _ConstantReference {
public:
	ConstantClass(u2 classIndex): _ConstantReference(classIndex) {}
public:
	inline const u2 getClassIndex() { return _index; }
};

class ConstantString: public _ConstantReference {
public:
	ConstantString(u2 stringIndex): _ConstantReference(stringIndex) {}
public:
	inline const u2 getStringIndex() { return _index; }
};

/*
 * CONSTANT_Fieldref_info
 * CONSTANT_Methodref_info
 * CONSTANT_InterfaceMethodref_info
 *
 */
class ConstantFieldOrMethodRef {
public:
	ConstantFieldOrMethodRef(u2 classIndex, u2 nameAndTypeIndex)
:_classIndex(classIndex), _nameAndTypeIndex(nameAndTypeIndex){};
public:
	inline const u2 getClassIndex() const { return _classIndex; }
	inline const u2 getNameAndTypeIndex() const { return _nameAndTypeIndex; }
protected:
	u2 _classIndex;
	u2 _nameAndTypeIndex;
};

/*
 * CONSTANT_Integer_info
 * CONSTANT_Float_info
 */
class ConstantNumber {
public:
	ConstantNumber(u4 bytes): _bytes(bytes){}
public:
	inline const u4 getBytes() const { return _bytes; }
protected:
	u4 _bytes;
};
}

#endif
