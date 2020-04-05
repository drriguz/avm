cmake_minimum_required (VERSION 2.6)

project (avm)

set(CMAKE_CXX_STANDARD 11)
set(GOOGLE_TEST_DIR    tests/lib/googletest-1.8.0)

if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(GOOGLE_TEST_LIB_DIR     ${GOOGLE_TEST_DIR}/msvc)
elseif(APPLE)
	set(GOOGLE_TEST_LIB_DIR     ${GOOGLE_TEST_DIR}/mac)
else()
	set(GOOGLE_TEST_LIB_DIR     ${GOOGLE_TEST_DIR}/linux)
endif()

include_directories(
	class_file/include
	vm/include)

add_library(
	class_file STATIC
	class_file/src/format/java_class.cpp
	class_file/src/format/class_property.cpp
	class_file/src/format/field_info.cpp
	class_file/src/format/method_info.cpp
	class_file/src/format/with_attributes.cpp
	class_file/src/format/constant_pool.cpp
	class_file/src/format/constant_pool_visitor.cpp
	class_file/src/format/constant/constant_info.cpp
	class_file/src/format/constant/utf8.cpp
	class_file/src/format/constant/class.cpp
	class_file/src/format/constant/ref.cpp
	class_file/src/format/constant/string.cpp
	class_file/src/format/constant/number.cpp
	class_file/src/format/constant/name_and_type.cpp
	class_file/src/format/constant/method_handle.cpp
	class_file/src/format/constant/method_type.cpp
	class_file/src/format/constant/invoke_dynamic.cpp
	class_file/src/parser/binary_reader.cpp
	class_file/src/parser/java_class_parser.cpp
	class_file/src/parser/class_file_parser.cpp
	class_file/src/helper/strings.cpp)

add_library(
	vm STATIC
    vm/src/runtime/virtual_machine.cpp
    vm/src/runtime/method_area.cpp
	vm/src/runtime/slot.cpp
	vm/src/runtime/operand_stack.cpp
	vm/src/runtime/local_variables.cpp
	vm/src/runtime/frame.cpp
	vm/src/util/numbers.cpp
    vm/src/class_loader.cpp
    vm/src/classpath_class_loader.cpp)

add_executable(avm_cli avm_cli/main.cpp)

if(WIN32)
	target_link_libraries(class_file LINK_PRIVATE wsock32)
endif()

target_link_libraries(vm      LINK_PUBLIC  class_file)
target_link_libraries(avm_cli LINK_PRIVATE class_file vm)

add_executable(
	tests
	tests/src/format/constant/test_number.cpp
	tests/src/format/constant/test_utf8.cpp
	tests/src/format/test_java_class.cpp
	tests/src/parser/test_binary_reader.cpp
	tests/src/parser/test_base_info.cpp
	tests/src/parser/test_constant_pool.cpp
	tests/src/parser/test_interfaces.cpp
	tests/src/parser/test_fields.cpp
	tests/src/parser/test_methods.cpp
	tests/src/helper/test_strings.cpp
	tests/src/vm/runtime/test_operand_stack.cpp
	tests/src/vm/runtime/test_local_variables.cpp
	tests/src/vm/test_classpath_class_loader.cpp
	tests/src/vm/test_method_area.cpp
	tests/src/vm/test_virtual_machine.cpp)
	
target_include_directories(tests PRIVATE ${GOOGLE_TEST_DIR}/include)

if(MSVC)
	find_library(GOOGLE_TEST_MAIN_DEBUG   gtest_main ${GOOGLE_TEST_LIB_DIR}/Debug)
	find_library(GOOGLE_TEST_DEBUG        gtest      ${GOOGLE_TEST_LIB_DIR}/Debug)
	find_library(GOOGLE_TEST_MAIN_RELEASE gtest_main ${GOOGLE_TEST_LIB_DIR}/Release)
	find_library(GOOGLE_TEST_RELEASE      gtest      ${GOOGLE_TEST_LIB_DIR}/Release)
	add_custom_command(
		TARGET tests POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory 
			${CMAKE_CURRENT_SOURCE_DIR}/tests/res
			${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/res)
else()
	find_library(GOOGLE_TEST_MAIN gtest_main ${GOOGLE_TEST_LIB_DIR})
	find_library(GOOGLE_TEST      gtest      ${GOOGLE_TEST_LIB_DIR})
	add_custom_command(
		TARGET tests POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory 
			${CMAKE_CURRENT_SOURCE_DIR}/tests/res
			${CMAKE_CURRENT_BINARY_DIR}/res/)
endif()

if(UNIX)
	target_link_libraries(tests LINK_PRIVATE class_file vm ${GOOGLE_TEST} ${GOOGLE_TEST_MAIN} pthread)
elseif(MSVC)
	target_link_libraries(tests LINK_PRIVATE class_file vm
		debug ${GOOGLE_TEST_DEBUG}      optimized ${GOOGLE_TEST_RELEASE}
		debug ${GOOGLE_TEST_MAIN_DEBUG} optimized ${GOOGLE_TEST_MAIN_RELEASE})
else()
	target_link_libraries(tests LINK_PRIVATE class_file vm ${GOOGLE_TEST} ${GOOGLE_TEST_MAIN})
endif()
