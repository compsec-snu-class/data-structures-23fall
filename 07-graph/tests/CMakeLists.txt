find_package(Catch2 REQUIRED)

add_executable(graph_test
  graph_test.cpp
  )

target_include_directories(graph_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(graph_test PUBLIC graph Catch2::Catch2)

target_compile_features(graph_test PUBLIC cxx_std_17)
