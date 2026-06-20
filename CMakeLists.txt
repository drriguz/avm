cmake_minimum_required (VERSION 3.11)

project (avm)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	add_compile_definitions(_ARCH_X64_)
endif()

include_directories(
	class_file/include
	vm/include)

add_library(
	class_file STATIC
	class_file/src/format/java_class.cpp
	class_file/src/format/descriptor_type.cpp
	class_file/src/format/class_property.cpp
	class_file/src/format/field_info.cpp
	class_file/src/format/method_info.cpp
	class_file/src/format/with_attributes.cpp
	class_file/src/format/instruction.cpp
	class_file/src/format/attribute/attribute_info.cpp
	class_file/src/format/attribute/constant_value.cpp
	class_file/src/format/attribute/code.cpp
	class_file/src/format/attribute/exception_table.cpp
	class_file/src/format/attribute/exceptions.cpp
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
	class_file/src/parser/file_reader.cpp
	class_file/src/parser/java_class_parser.cpp
	class_file/src/helper/strings.cpp)

add_library(
	vm STATIC
    vm/src/virtual_machine.cpp
	vm/src/interpreter.cpp
	vm/src/interpreter/constants.cpp
	vm/src/interpreter/loads.cpp
	vm/src/interpreter/stores.cpp
	vm/src/interpreter/stack.cpp
	vm/src/interpreter/math.cpp
	vm/src/interpreter/conversions.cpp
	vm/src/interpreter/comparisons.cpp
	vm/src/interpreter/control.cpp
	vm/src/interpreter/references.cpp
	vm/src/interpreter/extended.cpp
	vm/src/interpreter/reserved.cpp
	vm/src/runtime/heap.cpp
    vm/src/runtime/method_area.cpp
	vm/src/runtime/operand_stack.cpp
	vm/src/runtime/local_variables.cpp
	vm/src/runtime/frame.cpp
	vm/src/runtime/vm_thread.cpp
	vm/src/runtime/vm_stack.cpp
	vm/src/runtime/vm_method.cpp
	vm/src/runtime/vm_class.cpp
	vm/src/runtime/vm_field.cpp
	vm/src/util/numbers.cpp
    vm/src/class_loader.cpp
    vm/src/classpath_class_loader.cpp)

add_executable(avm_cli avm_cli/main.cpp)

if(WIN32)
	target_link_libraries(class_file LINK_PRIVATE wsock32)
endif()

target_link_libraries(vm      LINK_PUBLIC  class_file)
target_link_libraries(avm_cli LINK_PRIVATE class_file vm)

# Google Test — build from source using FetchContent
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
	tests
	tests/src/format/constant/test_number.cpp
	tests/src/format/constant/test_utf8.cpp
	tests/src/format/test_java_class.cpp
	tests/src/format/test_descriptor_parsing.cpp
	tests/src/parser/test_binary_reader.cpp
	tests/src/parser/test_base_info.cpp
	tests/src/parser/test_constant_pool.cpp
	tests/src/parser/test_interfaces.cpp
	tests/src/parser/test_fields.cpp
	tests/src/parser/test_methods.cpp
	tests/src/parser/test_mnemonic_mapping.cpp
	tests/src/helper/test_strings.cpp
	tests/src/vm/util/test_numbers.cpp
	tests/src/vm/runtime/test_operand_stack.cpp
	tests/src/vm/runtime/test_local_variables.cpp
	tests/src/vm/runtime/test_vm_class.cpp
	tests/src/vm/runtime/test_vm_field.cpp
	tests/src/vm/runtime/test_heap.cpp
	tests/src/vm/test_classpath_class_loader.cpp
	tests/src/vm/test_method_area.cpp
	tests/src/vm/test_virtual_machine.cpp
	tests/src/vm/interpreter/test_invoke_references_instructions.cpp
	tests/src/vm/interpreter/test_instructions.cpp
	)

target_link_libraries(tests LINK_PRIVATE class_file vm GTest::gtest_main)

add_custom_command(
	TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/tests/res
		${CMAKE_CURRENT_BINARY_DIR}/res/)
