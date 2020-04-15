#include "gtest/gtest.h"

#include "vm/runtime/vm_class.h"
#include "class_file/parser/java_class_parser.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(VmClass, initializeConstantField) {
    JavaClassParser parser1("res/com/test/Fields.class");
    auto javaClass = std::unique_ptr<JavaClass>(new JavaClass());
    parser1.parse(*javaClass.get());

    VmClass vmClass(std::move(javaClass));

    VmField* field1 = vmClass.getField("msg");
    VmField* field2 = vmClass.getField("pi");
    VmField* field3 = vmClass.getField("year");
    ASSERT_TRUE(field2);
    ASSERT_TRUE(field3);
    ASSERT_EQ(2020, field3->getInt());
    ASSERT_FLOAT_EQ(3.14, field2->getFloat());
}