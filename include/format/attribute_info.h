#ifndef _AVM_ATTRIBUTE_INFO_H_
#define _AVM_ATTRIBUTE_INFO_H_

#include "types.h"
#include "exception_table.h"

namespace avm {

struct AttributeInfo {
	u2 attributeNameIndex;
	u2 attributeLength;
	u1* info;
};

struct ConstantValue {
	u2 constantValueIndex;
};

struct Code {
	u2 maxStack;
	u2 maxLocals;
	u4 codeLength;
	u1* code;
	u2 exceptionTableLength;
	ExceptionTable* exceptionTable;
	u2 attributesCount;
	AttributeInfo* attributes;
};

struct StackMapTable {
	u2 numberOfEntries;

};

struct Synthetic {

};

struct Deprecated {

};

struct Singuature {
	u2 signatureIndex;
};

struct RuntimeVisibleAnnotations {
	u2 numberOfAnnotations;

};

struct RuntimeInVisibleAnnotations {

};
}

#endif
