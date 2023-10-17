cmake_minimum_required(VERSION 3.15)

project(rbtree)

set(CMAKE_BUILD_TYPE Debug)

add_library(rbtree INTERFACE)

target_include_directories(rbtree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(rbtree INTERFACE cxx_std_17)

add_subdirectory(examples)

add_subdirectory(tests)
