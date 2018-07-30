
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

if(NOT sf_git_error_code)
  sf_create_executable(
    tests
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
    DEPENDS Catch ${EDEN_LIB}
    FOLDER Tests
  )

  # CTest
  add_test(NAME unit COMMAND tests)
endif()
