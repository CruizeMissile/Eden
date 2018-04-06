
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

create_library(eden SOURCE_LIST ${eden_files} CXX_VERSION 17)
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
