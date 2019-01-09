cmake_minimum_required(VERSION 3.11)
project(SH_CPP_LIB_DEV C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)
APPEND_COVERAGE_COMPILER_FLAGS()

find_package(Threads REQUIRED)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(SH_CppLib)

add_subdirectory(test)
