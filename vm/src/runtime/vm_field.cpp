#include "vm/runtime/vm_field.h"

using namespace avm;

VmField::VmField(const std::string& name, const std::string& descriptor):
    _name(name),
    _descriptor(descriptor),
    _value(0) {

}

VmField::~VmField() {

}