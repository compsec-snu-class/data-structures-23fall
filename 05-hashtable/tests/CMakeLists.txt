find_package(Catch2 REQUIRED)

add_executable(hashtable_test
  hashtable_test.cpp
  )

target_include_directories(hashtable_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(hashtable_test PUBLIC hashtable Catch2::Catch2)

target_compile_features(hashtable_test PUBLIC cxx_std_17)
