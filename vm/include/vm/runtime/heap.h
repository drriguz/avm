#ifndef _AVM_HEAP_H_
#define _AVM_HEAP_H_

#include "slot.h"
#include "object.h"
#include "vm_class.h"

namespace avm {

class Heap {
public:
    Heap(int size);
    virtual ~Heap();
public:
    Object newInstance(const VmClass& type);
protected:
    int _freePosition;
    int _maxSize;
    OBJECT_UNIT* _data;
};
}
#endif
