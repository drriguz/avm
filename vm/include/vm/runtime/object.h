#ifndef _AVM_OBJECT_H_
#define _AVM_OBJECT_H_

#include <map>
#include <string>
#include <cstdint>

#include "vm_class.h"
#include "vm_field.h"
#include "slot.h"

namespace avm {

class Object {
protected:
    VmClass *_class;
    Slot* _data;
};
}
#endif
