#include "gtest/gtest.h"
#include "vm/runtime/heap.h"
#include "vm/runtime/method_area.h"
#include "vm/classpath_class_loader.h"
#include "vm/exceptions.h"

#include <iostream>

using namespace avm;

TEST(Heap, newInstance) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    auto loaded = loader.load("com/test/complex/MemoryDb", &methodArea);

    Heap heap(5);
    Object instance = heap.newInstance(*loaded.get());
}

TEST(Heap, throwExceptionIfHeapIsFull) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    auto loaded = loader.load("com/test/complex/MemoryDb", &methodArea);

    Heap heap(1);
    EXPECT_THROW(heap.newInstance(*loaded.get()), OutOfMemoryException);
}

