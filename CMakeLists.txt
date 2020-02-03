cmake_minimum_required (VERSION 2.6)

project (avm)

set(CMAKE_CXX_STANDARD 11)

include_directories(
	include
)

find_library(
    GOOGLE_TEST_MAIN
    gtest_main
    lib/googletest
)

find_library(
    GOOGLE_TEST
    gtest
    lib/googletest
)

find_library(
    GOOGLE_TEST_MOCK
    gmock
    lib/googletest
)

add_library(
	java_class_parser
	SHARED
	src/format/java_class.cpp
	src/format/class_property.cpp
	src/format/field_info.cpp
	src/format/method_info.cpp
	src/format/with_attributes.cpp
	src/format/constant/constant_info.cpp
	src/format/constant/utf8.cpp
	src/format/constant/class.cpp
	src/format/constant/ref.cpp
	src/format/constant/string.cpp
	src/format/constant/number.cpp
	src/format/constant/name_and_type.cpp
	src/format/constant/method_handle.cpp
	src/format/constant/method_type.cpp
	src/format/constant/invoke_dynamic.cpp
	src/parser/java_class_parser.cpp
	src/parser/class_file_parser.cpp
)

add_library(
    java_vm
    SHARED
    src/helper/strings.cpp
    src/vm/virtual_machine.cpp
    src/vm/method_area.cpp
    src/vm/class_loader.cpp
    src/vm/classpath_class_loader.cpp
)

add_executable(guava src/main.cpp)

add_executable(
	unit_test
	
	test/src/format/constant/test_utf8.cpp
	test/src/parser/test_base_info.cpp
	test/src/parser/test_constant_pool.cpp

	test/src/parser/test_interfaces.cpp
	test/src/parser/test_fields.cpp
	test/src/parser/test_methods.cpp
	
	test/src/helper/test_strings.cpp
	
	# test/src/vm/test_classpath_class_loader.cpp
	# test/src/vm/test_method_area.cpp
)

file(
	GLOB
	TEST_RESOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/test/res
)
    
file(
    COPY
    ${TEST_RESOURCES}
    DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}
) 

#[[
    Tested env:
    java version "1.8.0_231"
    Java(TM) SE Runtime Environment (build 1.8.0_231-b11)
    Java HotSpot(TM) 64-Bit Server VM (build 25.231-b11, mixed mode)
]]#
add_custom_target(
    compiledTestClass
    ALL
    
    COMMAND find ${CMAKE_CURRENT_BINARY_DIR}/res -name "*.java" -print | xargs javac
    COMMENT "Compiling java files..."
)
    
target_include_directories(
	unit_test
	PRIVATE
	lib/googletest/include
)

target_link_libraries(
	java_vm
	LINK_PUBLIC
	java_class_parser
)

target_link_libraries(
    guava
    LINK_PUBLIC
    java_class_parser
    java_vm
)

target_link_libraries(
    unit_test
    LINK_PUBLIC
    java_class_parser
    java_vm
    ${GOOGLE_TEST}
    ${GOOGLE_TEST_MAIN}
)
    