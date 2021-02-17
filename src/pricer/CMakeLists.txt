file(GLOB SOURCES *.cpp)

add_library(pricer INTERFACE)
target_include_directories(pricer INTERFACE
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_sources(pricer INTERFACE ${SOURCES})