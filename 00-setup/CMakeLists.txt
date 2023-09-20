cmake_minimum_required(VERSION 3.15)

project(hello)

add_library(hello INTERFACE)

target_include_directories(hello INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(hello INTERFACE cxx_std_17)

set(CMAKE_BUILD_TYPE Debug)    

add_subdirectory(tests)

add_subdirectory(examples)
