#include "gtest/gtest.h"

#include <iostream>
#include "vm/classpath_class_loader.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(ClasspathClassLoader, parseClass) {
    ClasspathClassLoader loader("res");
    try {
        auto loaded = loader.load("com/test/Simple");
    } catch (std::exception const &err) {
        FAIL() << err.what();
    }
}

TEST(ClasspathClassLoader, throwExceptionIfClassNotFound) {
    ClasspathClassLoader loader("res");
    EXPECT_THROW(loader.load("com/test/NotExist"),
                 ClassNotFoundException);
}

