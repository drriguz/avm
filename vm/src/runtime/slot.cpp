#include "vm/runtime/slot.h"

using namespace avm;

Slot::Slot() :
    _value(0) {
}

Slot::Slot(uint32_t value) :
    _value(value) {
}

Slot::Slot(const Slot &p) :
    _value(p._value) {
}

Slot::~Slot() {
}
