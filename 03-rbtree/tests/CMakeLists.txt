find_package(Catch2 REQUIRED)

add_executable(rbtree_test
  rbtree_test.cpp
  )

target_include_directories(rbtree_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(rbtree_test PUBLIC rbtree Catch2::Catch2)

target_compile_features(rbtree_test PUBLIC cxx_std_17)

add_executable(rbtree_delete_test
  rbtree_delete_test.cpp
  )

target_include_directories(rbtree_delete_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(rbtree_delete_test PUBLIC rbtree Catch2::Catch2)

target_compile_features(rbtree_delete_test PUBLIC cxx_std_17)
