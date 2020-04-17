#include "gtest/gtest.h"

#include <iostream>
#include "vm/classpath_class_loader.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(ClasspathClassLoader, parseClass) {
    MethodArea methodArea;
    ClasspathClassLoader loader(&methodArea, "res");
    try {
        JavaClass loaded;
        loader.loadClass("com.test.Simple", loaded);
    } catch (std::exception const &err) {
        FAIL() << err.what();
    }
}

TEST(ClasspathClassLoader, throwExceptionIfClassNotFound) {
    MethodArea methodArea;
    ClasspathClassLoader loader(&methodArea, "res");
    JavaClass loaded;
    EXPECT_THROW(loader.loadClass("com.test.NotExist", loaded),
                 ClassNotFoundException);
}

