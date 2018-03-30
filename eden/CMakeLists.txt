
file(GLOB_RECURSE eden_files
  "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)
add_library(eden "${eden_files}")
target_common_compiler_flags(eden)
target_source_group(eden)
