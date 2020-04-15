#include "gtest/gtest.h"

#include <iostream>

#include "class_file/parser/java_class_parser.h"
#include "vm/runtime/method_area.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(MethodArea, throwExceptionIfClassNotFound) {
    MethodArea methodArea;
    EXPECT_THROW(methodArea.getClass("com.riguz.Simple"),
                 ClassNotFoundException);
}

TEST(MethodArea, getClassIfClassFound) {
    MethodArea methodArea;
    JavaClassParser parser("res/com/test/Simple.class");
    auto javaClass = std::unique_ptr<JavaClass>(new JavaClass());
    parser.parse(*javaClass.get());
    auto vmClass= std::unique_ptr<VmClass>(new VmClass(std::move(javaClass)));

    methodArea.putClass("com.riguz.Simple", std::move(vmClass));
    try {
        const JavaClass *actual = methodArea.getClass("com.riguz.Simple")->getClass();

        ASSERT_EQ(0xCAFEBABE, actual->getMagic());
        ASSERT_EQ(52, actual->getMajorVersion());
        ASSERT_EQ(0, actual->getMinorVersion());
    } catch (std::exception const &err) {
        FAIL() << err.what();
    }
}

TEST(MethodArea, throwExceptionIfClassExists) {
    MethodArea methodArea;
    JavaClassParser parser("res/com/test/Simple.class");
    auto javaClass = std::unique_ptr<JavaClass>(new JavaClass());
    parser.parse(*javaClass.get());
    auto vmClass= std::unique_ptr<VmClass>(new VmClass(std::move(javaClass)));
    methodArea.putClass("com.riguz.Simple", std::move(vmClass));
    EXPECT_THROW(methodArea.putClass("com.riguz.Simple", std::move(vmClass)),
                 ClassAlreadyLoadedException);
}
