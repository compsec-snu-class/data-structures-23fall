find_package(Catch2 REQUIRED)

add_executable(btree_test
  btree_test.cpp
  )

target_include_directories(btree_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(btree_test PUBLIC btree Catch2::Catch2)

target_compile_features(btree_test PUBLIC cxx_std_17)

add_executable(btree_delete_test
  btree_delete_test.cpp
  )

target_include_directories(btree_delete_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(btree_delete_test PUBLIC btree Catch2::Catch2)

target_compile_features(btree_delete_test PUBLIC cxx_std_17)

# add_executable(btree_fuzz
#   btree_fuzz.cpp
#   )

# target_include_directories(btree_fuzz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# target_compile_options(btree_fuzz
#   PRIVATE $<$<C_COMPILER_ID:Clang>:-g -O1 -fsanitize=fuzzer,address>)

# target_link_libraries(btree_fuzz PUBLIC btree ssl crypto
#   $<$<C_COMPILER_ID:Clang>:-fsanitize=fuzzer,address>)

# target_compile_features(btree_fuzz PUBLIC cxx_std_17)
