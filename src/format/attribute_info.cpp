#include "format/attribute_info.h"

using namespace avm;

AttributeInfo::~AttributeInfo() {
	if (info)
		delete info;
}

void AttributeInfo::ensureAttributes() {
	if (info)
		delete info;
}
