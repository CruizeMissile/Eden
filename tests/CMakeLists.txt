
enable_testing()
include(git_clone)

git_clone(catch "https://github.com/cruizemissile/catch2" "${CMAKE_SOURCE_DIR}/external")

option(CATCH_USE_VALGRIND "Perform SelfTests with Valgrind" OFF)
option(CATCH_BUILD_EXAMPLES "Build documentation examples" OFF)
option(CATCH_ENABLE_COVERAGE "Generate coverage for codecov.io" OFF)
option(CATCH_ENABLE_WERROR "Enable all warnings as errors" ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/external/catch" "${CMAKE_BINARY_DIR}/external/catch")
file(GLOB_RECURSE test_files
  *.h *.hpp *.cpp
)
add_executable(tests "${test_files}")
target_include_directories(tests PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(tests Catch eden)
target_source_group(tests)
target_set_folder(tests Tests)

# CTest
add_test(NAME unit COMMAND tests)
