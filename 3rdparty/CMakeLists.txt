##
## Glfw
##
set(GLFW_BUILD_EXAMPLES FALSE CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS FALSE CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS FALSE CACHE BOOL "" FORCE)
set(GLFW_INSTALL FALSE CACHE BOOL "" FORCE)
set(GLFW_LIBRARY "glfw" PARENT_SCOPE)
get_filename_component(GLFW_DIR "./glfw/" ABSOLUTE)
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include PARENT_SCOPE)
add_subdirectory("glfw/")

##
## Cml
##
add_subdirectory(cml)
# get_filename_component(CML_DIR "./cml/" ABSOLUTE)
# set(CML_INCLUDE_DIR ${CML_DIR}/cml PARENT_SCOPE)
# add_library(cml INTERFACE)
# target_include_directories(cml INTERFACE ${CML_INCLUDE_DIR})
# add_subdirectory("cml/")

##
## Catch
##
set(NO_SELFTEST TRUE CACHE BOOL "" FORCE)
get_filename_component(CATCH_DIR "./Catch" ABSOLUTE)
set(CATCH_INCLUDE_DIR ${CATCH_DIR}/single_include PARENT_SCOPE)
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ${CATCH_INCLUDE_DIR})
add_subdirectory("Catch/")

##
## Loguru
##
get_filename_component(LOGURU_DIR "./loguru" ABSOLUTE)
add_library(loguru INTERFACE)
target_sources(loguru INTERFACE "${LOGURU_DIR}/loguru.hpp")

##
## cmake resources
##
# https://stackoverflow.com/questions/39887352/how-to-create-a-cmake-header-only-library-that-depends-on-external-header-files
