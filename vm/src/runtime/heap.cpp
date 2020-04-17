#include "vm/runtime/heap.h"

using namespace avm;

Heap::Heap(int size)
    :_freePosition(0),
     _maxSize(size),
     _data(new uint8_t[size]) {

}

Heap::~Heap() {
    delete[] _data;
}