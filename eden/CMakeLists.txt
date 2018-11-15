
list(APPEND eden_files
  "${CMAKE_CURRENT_LIST_DIR}/app/app.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/app.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/event.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/event.inl"
  "${CMAKE_CURRENT_LIST_DIR}/app/input.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/input.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/window.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/app/window.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/ecs/archetype.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/archetype.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/defines.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/director.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/director.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/director.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/dispatcher.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/dispatcher.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/dispatcher.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/entity.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/entity.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/entity.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/id.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/mask.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/pool.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/property.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/property.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/store.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/store.inl"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/system.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/system.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs/utils.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/ecs.hpp"
)

sf_create_library(eden
  SOURCE_LIST ${eden_files}
  CXX_VERSION 17
  INCLUDE_DIR ${PROJECT_SOURCE_DIR} ${GLFW_INCLUDE_DIR}
  DEPENDS ${GLFW_LIBRARY} ${PRIDE_LIB}
)
