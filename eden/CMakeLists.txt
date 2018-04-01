
file(GLOB_RECURSE eden_files
  "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/*.inl"
  "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)
add_library(eden "${eden_files}")
target_link_libraries(eden libpride)
target_common_compiler_flags(eden)
target_source_group(eden)
target_include_directories(eden PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

