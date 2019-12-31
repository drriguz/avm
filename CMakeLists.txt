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
	src/format/constant_pool.cpp
	src/format/class_property.cpp
	src/format/field_info.cpp
	src/format/method_info.cpp
	src/format/with_attributes.cpp
	src/parser/java_class_parser.cpp
	src/parser/class_file_parser.cpp
	
)

add_executable(guava src/main.cpp)

add_executable(
	unit_test
	test/src/parser/test_base_info.cpp
	test/src/parser/test_constant_pool.cpp
	test/src/parser/test_interfaces.cpp
	test/src/parser/test_fields.cpp
	test/src/parser/test_methods.cpp
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
	guava
	LINK_PUBLIC
	java_class_parser
)

target_link_libraries(
    unit_test
    LINK_PUBLIC
    java_class_parser
    ${GOOGLE_TEST}
    ${GOOGLE_TEST_MAIN}
)
    