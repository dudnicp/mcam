add_subdirectory(pricer)

add_executable(mcam mcam.cpp)
target_link_libraries(mcam jl_parser pricer ${LIBS})
set_target_properties(mcam
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")