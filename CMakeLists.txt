cmake_minimum_required(VERSION 3.2...3.28.3)

project(Homework_prog_2025)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(HoareSort)
add_subdirectory(refactoring)
add_subdirectory(unit_test_HoareSort)

set(CMAKE_SUPPRESS_REGENERATION true)
