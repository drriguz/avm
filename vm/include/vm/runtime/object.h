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
public:
    Object(Slot* data, int size): _data(data), _size(size) {}
    Object(const Object& p): _data(p._data), _size(p._size) {}
    virtual ~Object() {}
protected:
    Slot* _data;
    int _size;
};
}
#endif
