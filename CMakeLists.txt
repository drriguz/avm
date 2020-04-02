cmake_minimum_required (VERSION 2.6)

project (avm)

set(CMAKE_CXX_STANDARD 11)
if(WIN32)
	set(GOOGLE_TEST_DIR tests/lib/googletest-1.8.0)
	set(GOOGLE_TEST_LIB_DIR tests/lib/googletest-1.8.0/mdd)
else()
	set(GOOGLE_TEST_DIR tests/lib/googletest)
	set(GOOGLE_TEST_LIB_DIR tests/lib/googletest)
endif()

include_directories(
	class_parser/include
	vm/include
)

add_library(
	class_parser
	STATIC
	class_parser/src/format/java_class.cpp
	class_parser/src/format/class_property.cpp
	class_parser/src/format/field_info.cpp
	class_parser/src/format/method_info.cpp
	class_parser/src/format/with_attributes.cpp
	class_parser/src/format/constant/constant_info.cpp
	class_parser/src/format/constant/utf8.cpp
	class_parser/src/format/constant/class.cpp
	class_parser/src/format/constant/ref.cpp
	class_parser/src/format/constant/string.cpp
	class_parser/src/format/constant/number.cpp
	class_parser/src/format/constant/name_and_type.cpp
	class_parser/src/format/constant/method_handle.cpp
	class_parser/src/format/constant/method_type.cpp
	class_parser/src/format/constant/invoke_dynamic.cpp
	
	class_parser/src/parser/binary_reader.cpp
	class_parser/src/parser/java_class_parser.cpp
	class_parser/src/parser/class_file_parser.cpp
	
	class_parser/src/helper/strings.cpp
)

add_library(
    vm
    STATIC
    vm/src/virtual_machine.cpp
    vm/src/method_area.cpp
    vm/src/class_loader.cpp
    vm/src/classpath_class_loader.cpp
)

add_executable(
	avm_cli
	avm_cli/main.cpp
)

find_library(
    GOOGLE_TEST_MAIN
    gtest_main
    ${GOOGLE_TEST_LIB_DIR}
)

find_library(
    GOOGLE_TEST
    gtest
    ${GOOGLE_TEST_LIB_DIR}
)

find_library(
    GOOGLE_TEST_MOCK
    gmock
    lib/googletest
)

add_executable(
	tests
	
	tests/src/format/constant/test_number.cpp
	tests/src/format/constant/test_utf8.cpp
	
	tests/src/parser/test_binary_reader.cpp
	tests/src/parser/test_base_info.cpp
	tests/src/parser/test_constant_pool.cpp
	tests/src/parser/test_interfaces.cpp
	tests/src/parser/test_fields.cpp
	tests/src/parser/test_methods.cpp
	
	tests/src/helper/test_strings.cpp
	
	tests/src/vm/test_classpath_class_loader.cpp
	tests/src/vm/test_method_area.cpp
)

target_include_directories(
	tests
	PRIVATE
	${GOOGLE_TEST_DIR}/include
)

if(WIN32)
	target_link_libraries(class_parser wsock32)
endif()

target_link_libraries(
	vm
	LINK_PUBLIC
	class_parser
)

target_link_libraries(
    avm_cli
    LINK_PUBLIC
    class_parser
    vm
)

target_link_libraries(
    tests
    LINK_PUBLIC
    class_parser
    vm
    ${GOOGLE_TEST}
    ${GOOGLE_TEST_MAIN}
)
    