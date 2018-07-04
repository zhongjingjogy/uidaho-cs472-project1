cmake_minimum_required (VERSION 2.8)

file (GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/examples/quadratic/*.cpp)

set (SOURCE_FILES ${CPP_FILES})

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

add_executable(quadratic ${SOURCE_FILES})

target_link_libraries(quadratic ec)