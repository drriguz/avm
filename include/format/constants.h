#ifndef _AVM_CONSTANTS_H_
#define _AVM_CONSTANTS_H_

#include "types.h"

namespace avm {
enum ConstantTypes {
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

struct CONSTANT_Class {
	u1 tag;
	u2 name_index;
};

struct CONSTANT_Fieldref_info {
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_Methodref_info {
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
	u1 tag;
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_String_info {
	u1 tag;
	u2 string_index;
};

struct CONSTANT_Integer_info {
	u1 tag;
	u4 bytes;
};

struct CONSTANT_Float_info {
	u1 tag;
	u4 bytes;
};

struct CONSTANT_Long_info {
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
};

struct CONSTANT_Double_info {
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
};

struct CONSTANT_NameAndType_info {
	u1 tag;
	u2 name_index;
	u2 descriptor_index;
};

struct CONSTANT_Utf8_info {
	u1 tag;
	u2 length;
	u1* bytes;
};
}

#endif
