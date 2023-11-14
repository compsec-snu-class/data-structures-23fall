cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

project(hashtable)

add_library(hashtable INTERFACE)

target_include_directories(hashtable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(hashtable INTERFACE cxx_std_17)

add_subdirectory(examples)

add_subdirectory(tests)
