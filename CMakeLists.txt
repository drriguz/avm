cmake_minimum_required(VERSION 3.13)
project(avm)

set(CMAKE_CXX_STANDARD 11)

include_directories(
  include
  3rd/spdlog/include
)

add_library(
  class_parser
  SHARED
  src/class_parser.cpp
  src/format/class_file.cpp
  src/format/attribute_info.cpp
  src/format/constant_visitor.cpp
  src/format/field_info.cpp
  src/utils/ieee754.cpp
)

find_library(
  SPDLOG_LIB
  spdlog
  3rd/spdlog
)

find_library(
  GOOGLE_TEST_MAIN
  gtest_main
  3rd/googletest
)

find_library(
  GOOGLE_TEST
  gtest
  3rd/googletest
)

find_library(
  GOOGLE_MOCK
  gmock
  3rd/googletest
)

add_executable(avm main.cpp)

target_link_libraries(
  avm
  LINK_PUBLIC
  ${SPDLOG_LIB}
  class_parser
)

add_executable(avm_test test/ieee754_test.cpp)
target_include_directories(
  avm_test
  PRIVATE
  3rd/googletest/include
)
target_link_libraries(
  avm_test
  LINK_PUBLIC
  class_parser
  ${GOOGLE_TEST}
  ${GOOGLE_TEST_MAIN}
)

