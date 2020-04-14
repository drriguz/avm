#include "class_file/format/attribute/code.h"

using namespace avm;

Code::Code(u2  maxStack, u2  maxLocals):
    _maxStack(maxStack),
    _maxLocals(maxLocals),
    AttributeInfo(AttributeType::CODE) {
}

Code:: ~Code() {
}