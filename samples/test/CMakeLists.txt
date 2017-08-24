
# set the name of the sample
set(SAMPLE_NAME "${PROJECT_NAME}-sample")

file(GLOB_RECURSE srcs ./*.cpp)
add_executable(${SAMPLE_NAME} ${srcs})
target_link_libraries(${SAMPLE_NAME} eden)
set_filter_groups("${_source_list}")
