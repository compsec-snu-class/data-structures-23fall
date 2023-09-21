find_package(Catch2 REQUIRED)

add_executable(deque_test
  deque_test.cpp
  )

target_include_directories(deque_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(deque_test PUBLIC deque Catch2::Catch2)

target_compile_features(deque_test PUBLIC cxx_std_17)


add_executable(palindrome_test
  palindrome_test.cpp
  )

target_include_directories(palindrome_test PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCe_DIR}/palindrome/include
  )

target_link_libraries(palindrome_test PUBLIC deque palindrome Catch2::Catch2)

target_compile_features(palindrome_test PUBLIC cxx_std_17)
