find_package(Catch2 REQUIRED)

add_executable(BST_test
  BST_test.cpp
  )

target_include_directories(BST_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(BST_test PUBLIC BST Catch2::Catch2)

target_compile_features(BST_test PUBLIC cxx_std_17)
