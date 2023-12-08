cmake_minimum_required(VERSION 3.10)

project(graph)

add_library(graph INTERFACE)

target_include_directories(graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(graph INTERFACE cxx_std_17)

add_subdirectory(examples)

add_subdirectory(tests)
