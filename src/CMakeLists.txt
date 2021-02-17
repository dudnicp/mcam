add_subdirectory(pricer)

add_executable(mc-example mc_example.cpp)
target_link_libraries(mc-example jl_parser pricer ${LIBS})
set_target_properties(mc-example
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")