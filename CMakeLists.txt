cmake_minimum_required(VERSION 3.15)
project(tvector_tmatrix_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------
# Library
# -----------------------

add_library(my_lib STATIC
  src/TExpressionSolver.cpp
  # add ALL .cpp files here
)

target_include_directories(my_lib
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

# -----------------------
# Testing
# -----------------------

enable_testing()

add_subdirectory(external/googletest)

add_executable(unit_tests
  tests/test_tarithmetic.cpp
)

target_link_libraries(unit_tests
  PRIVATE my_lib
  PRIVATE gtest_main
)

add_test(NAME unit_tests COMMAND unit_tests)
