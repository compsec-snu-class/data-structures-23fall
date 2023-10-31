cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE Debug)

project(btree)

add_library(btree INTERFACE)

target_include_directories(btree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(btree INTERFACE cxx_std_17)

add_subdirectory(examples)

add_subdirectory(tests)
