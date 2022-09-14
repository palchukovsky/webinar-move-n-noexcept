cmake_minimum_required(VERSION 3.15)

project(20.move_n_noexcept)

add_executable(1_rvo 1_rvo.cpp)
add_executable(2_values 2_values.cpp)
add_executable(3_move 3_move.cpp)
add_executable(4_universal_references 4_universal_references.cpp)

set_target_properties(
  1_rvo 2_values 3_move 4_universal_references
  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_library(common INTERFACE)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
  CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(common INTERFACE
    INTERFACE
      -g
      -Wall
      -Wextra
      -Werror
      -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(common INTERFACE
    INTERFACE
      /EHsc
      /W4
      /WX)
endif()

target_link_libraries(1_rvo PRIVATE common)
target_link_libraries(2_values PRIVATE common)
target_link_libraries(3_move PRIVATE common)
target_link_libraries(4_universal_references PRIVATE common)