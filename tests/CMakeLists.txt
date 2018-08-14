
enable_testing()

option(CATCH_USE_VALGRIND "Perform SelfTests with Valgrind" OFF)
option(CATCH_BUILD_EXAMPLES "Build documentation examples" OFF)
option(CATCH_ENABLE_COVERAGE "Generate coverage for codecov.io" OFF)
option(CATCH_ENABLE_WERROR "Enable all warnings as errors" ON)
sf_add_external_git_repo(
  URL "https://github.com/cruizemissile/catch2.git"
  TAG master
  PREFIX "external/catch"
  OPTIONAL
)

if(EXISTS ${CMAKE_SOURCE_DIR}/external/catch/.git)
  sf_create_executable(
    tests                                 # name of the test executable
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" # directory where scaffold will look for all the files
    DEPENDS Catch ${EDEN_LIB}             # the external libraries that this executable depends on
    FOLDER Tests                          # In an IDE this target will be under the folder "Tests"
  )

  # CTest
  add_test(NAME unit COMMAND tests)
endif()
