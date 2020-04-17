#ifndef _AVM_HEAP_H_
#define _AVM_HEAP_H_

#include "slot.h"

namespace avm {

class Heap {
public:
    Heap(int size);
    virtual ~Heap();
protected:
    int _freePosition;
    int _maxSize;
    uint8_t* _data;
};
}
#endif
