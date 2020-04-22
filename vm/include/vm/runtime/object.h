#ifndef _AVM_OBJECT_H_
#define _AVM_OBJECT_H_

#include <map>
#include <string>
#include <cstdint>

#include "vm_class.h"
#include "vm_field.h"

typedef uint64_t OBJECT_UNIT;

namespace avm {

class Object {
public:
    Object(OBJECT_UNIT* data, int size): _data(data), _size(size) {}
    Object(const Object& p): _data(p._data), _size(p._size) {}
    virtual ~Object() {}
protected:
    OBJECT_UNIT* _data;
    int _size;
};
}
#endif
