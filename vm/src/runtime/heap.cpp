#include "vm/runtime/heap.h"
#include "vm/exceptions.h"

using namespace avm;

Heap::Heap(int size)
    :_freePosition(0),
     _maxSize(size),
     _data(new OBJECT_UNIT[size]) {

}

Heap::~Heap() {
    delete[] _data;
}

Object Heap::newInstance(const VmClass& type) {
    int totalSlots = type.getSize();
    if(totalSlots == 0) totalSlots = 1; // minimum object size
    if(_freePosition + totalSlots > _maxSize)
        throw OutOfMemoryException("Heap is full");
    OBJECT_UNIT* startPos = _data + _freePosition;
    _freePosition += totalSlots;
    // Zero-initialize the object data
    for(int i = 0; i < totalSlots; i++) {
        startPos[i] = 0;
    }
    return Object(startPos, totalSlots);
}