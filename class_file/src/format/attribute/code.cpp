#include "class_file/format/attribute/code.h"

using namespace avm;

Code::Code(const u2& maxStack, const u2& maxLocals):
_maxStack(maxStack),
_maxLocals(maxLocals),
AttributeInfo(AttributeType::CODE) {
}

Code:: ~Code() {
}