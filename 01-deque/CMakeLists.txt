cmake_minimum_required(VERSION 3.15)

project(deque)

add_library(deque INTERFACE)

target_include_directories(deque INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(deque INTERFACE cxx_std_17)

set(CMAKE_BUILD_TYPE Debug)    

add_subdirectory(palindrome)

add_subdirectory(examples)

add_subdirectory(tests)
