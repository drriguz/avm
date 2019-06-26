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
)

find_library(
  SPDLOG_LIB
  spdlog
  3rd/spdlog
)

add_executable(avm main.cpp)

target_link_libraries(
  avm
  LINK_PUBLIC
  ${SPDLOG_LIB}
  class_parser
)