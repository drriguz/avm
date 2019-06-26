#include "format/field_info.h"

using namespace avm;

FieldInfo::~FieldInfo() {
	if (attributes)
		delete[] attributes;
}

void FieldInfo::ensureAttributes() {
	if (attributes)
		delete[] attributes;
	attributes = new AttributeInfo[attributes_count];
}
