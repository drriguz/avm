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

TEST(ClasspathClassLoader, resolveSuperClassAndInterfaces) {
    ClasspathClassLoader loader("res");
    auto loaded = loader.load("com/test/complex/MemoryDb");
    const JavaClass* superClass = loaded.get()->getSuperClass();
    ASSERT_NE(nullptr, superClass);
    ASSERT_STREQ("com/test/complex/Db", loaded->getSuperClass()->getClassName().c_str());
    auto interfaces = loaded.get()->getInterfaces();
    ASSERT_EQ(2, interfaces.size());
    ASSERT_STREQ("com/test/i/Imaginable", interfaces[0].get()->getClassName().c_str());
    ASSERT_STREQ("com/test/i/Store", interfaces[1].get()->getClassName().c_str());
}
