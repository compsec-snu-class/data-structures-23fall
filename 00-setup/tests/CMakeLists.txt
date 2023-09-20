find_package(Catch2 REQUIRED)

add_executable(hello_test
  hello_test.cpp
  )

target_include_directories(hello_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(hello_test PUBLIC hello Catch2::Catch2)

target_compile_features(hello_test PUBLIC cxx_std_17)
