cmake_minimum_required(VERSION 3.18)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

project(fibonacci_heap)

add_library(fheap INTERFACE)

target_include_directories(fheap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(fheap INTERFACE cxx_std_17)

add_subdirectory(examples)
add_subdirectory(tests)
