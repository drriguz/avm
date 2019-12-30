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
	src/parser/java_class_parser.cpp
	src/parser/class_file_parser.cpp
)

add_executable(avm avm.cpp)

add_executable(
	avm_test
	test/src/class_file_parser_test.cpp
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

add_custom_target(
    compiledTestClass
    ALL
    COMMAND find ${CMAKE_CURRENT_BINARY_DIR}/res -name "*.java" -print | xargs javac
    COMMENT "Compiling java files..."
)
    
target_include_directories(
	avm_test
	PRIVATE
	lib/googletest/include
)

target_link_libraries(
	avm
	LINK_PUBLIC
	java_class_parser
)

target_link_libraries(
    avm_test
    LINK_PUBLIC
    java_class_parser
    ${GOOGLE_TEST}
    ${GOOGLE_TEST_MAIN}
)
    