#ifndef _AVM_ANNOTATION_H_
#define _AVM_ANNOTATION_H_

#include "types.h"

namespace avm {

struct EnumConstValue {
	u2 typeNameIndex;
	u2 constNameIndex;
};



struct ElementValue {
	u1 tag;

};

struct ArrayValue {
	u2 numberOfValues;
	ElementValue* values;
};
struct ElementValuePair {
	u2 elementNameIndex;

};
struct Annotation {
	u2 typeIndex;
};
}

#endif
