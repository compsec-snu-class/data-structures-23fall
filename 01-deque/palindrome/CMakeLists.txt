cmake_minimum_required(VERSION 3.15)

add_library(palindrome INTERFACE)

target_include_directories(palindrome INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  include
  )

target_compile_features(palindrome INTERFACE cxx_std_17)

target_link_libraries(palindrome INTERFACE deque)
