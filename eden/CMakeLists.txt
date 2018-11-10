
list(APPEND eden_files
  "${CMAKE_CURRENT_LIST_DIR}/app/app.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/app.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/event.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/event.inl"
  "${CMAKE_CURRENT_LIST_DIR}/app/input.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/input.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/window.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/window.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/ecs/defines.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/id.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs.hpp"
)

sf_create_library(eden
  SOURCE_LIST ${eden_files}
  CXX_VERSION 17
  INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${GLFW_INCLUDE_DIR}
  DEPENDS ${GLFW_LIBRARY} ${PRIDE_LIB}
)
