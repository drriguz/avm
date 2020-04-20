#include "gtest/gtest.h"

#include <iostream>
#include "vm/classpath_class_loader.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(ClasspathClassLoader, parseClass) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    try {
        auto loaded = loader.load("com/test/Simple", &methodArea);
    } catch (std::exception const &err) {
        FAIL() << err.what();
    }
}

TEST(ClasspathClassLoader, throwExceptionIfClassNotFound) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    EXPECT_THROW(loader.load("com/test/NotExist", &methodArea),
                 ClassNotFoundException);
}

TEST(ClasspathClassLoader, resolveSuperClassAndInterfaces) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    auto loaded = loader.load("com/test/complex/MemoryDb", &methodArea);
    auto superClass = loaded->getSuperClass();
    ASSERT_NE(nullptr, superClass);
    ASSERT_STREQ("com/test/complex/Db", loaded->getSuperClass()->getClassName().c_str());
    auto interfaces = loaded->getInterfaces();
    ASSERT_EQ(2, interfaces.size());
    ASSERT_STREQ("com/test/i/Imaginable", interfaces[0]->getClassName().c_str());
    ASSERT_STREQ("com/test/i/Store", interfaces[1]->getClassName().c_str());
}

TEST(ClasspathClassLoader, prepareConstFieldValues) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    auto loaded = loader.load("com/test/Fields", &methodArea);
    auto vmClass = methodArea.getClass("com/test/Fields");

    VmField* field1 = vmClass->getField("msg");
    VmField* field2 = vmClass->getField("pi");
    VmField* field3 = vmClass->getField("year");
    ASSERT_TRUE(field1);
    ASSERT_TRUE(field2);
    ASSERT_TRUE(field3);
    ASSERT_EQ(2020, field3->getInt());
    ASSERT_FLOAT_EQ(3.14, field2->getFloat());
    ASSERT_STREQ("Hello world!", field1->getString().c_str());
}

TEST(ClasspathClassLoader, calculateInstanceFields) {
    MethodArea methodArea;
    ClasspathClassLoader loader("res");
    auto loaded = loader.load("com/test/complex/MemoryDb", &methodArea);
    auto child = methodArea.getClass("com/test/complex/MemoryDb");
    auto super = methodArea.getClass("com/test/complex/Db");

    VmField* field1 = child->getField("value");
    VmField* field2 = super->getField("id");

    ASSERT_TRUE(field1);
    ASSERT_TRUE(field2);

    ASSERT_EQ(1, field1->getSlotId());
    ASSERT_EQ(0, field2->getSlotId());
}