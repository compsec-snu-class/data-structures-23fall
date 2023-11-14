add_executable(example
  main.cpp
  )

target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(example PUBLIC hashtable)

target_compile_features(example PUBLIC cxx_std_17)
