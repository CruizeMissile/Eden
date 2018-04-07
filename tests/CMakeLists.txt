
enable_testing()

file(GLOB_RECURSE test_files
  *.h *.hpp *.cpp
)
add_executable(tests "${test_files}")
target_include_directories(tests PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(tests eden)
target_source_group(tests)
target_set_folder(tests Tests)

# CTest
add_test(NAME unit COMMAND tests)
