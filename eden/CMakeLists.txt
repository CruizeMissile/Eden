
list(APPEND eden_files
  "${CMAKE_CURRENT_LIST_DIR}/app/app.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/app.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/event.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/event.inl"
  "${CMAKE_CURRENT_LIST_DIR}/app/input.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/input.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/window.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/window.cpp"
)

add_library(eden "${eden_files}")
target_common_compiler_flags(eden)
target_set_cxx(eden 17)
gcc_clang_compile_flags(eden PUBLIC FLAGS "-std=c++1z")
target_source_group(eden)
target_include_directories(eden PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

#
# Dependencies
#

# glfw
target_include_directories(eden PUBLIC ${GLFW_INCLUDE_DIR})
target_link_libraries(eden PUBLIC ${GLFW_LIBRARY})

# pride
target_link_libraries(eden PUBLIC libpride)
