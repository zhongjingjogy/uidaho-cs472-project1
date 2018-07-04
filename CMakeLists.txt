cmake_minimum_required (VERSION 2.8)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/algorithm ${PROJECT_SOURCE_DIR}/include/algorithm/mutator ${PROJECT_SOURCE_DIR}/include/algorithm/recombinator ${PROJECT_SOURCE_DIR}/include/individual ${PROJECT_SOURCE_DIR}/include/problem)

SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fvisibility=hidden")

file (GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/algorithm/*.cpp ${PROJECT_SOURCE_DIR}/src/algorithm/mutator/*.cpp ${PROJECT_SOURCE_DIR}/src/algorithm/recombinator/*.cpp ${PROJECT_SOURCE_DIR}/src/individual/*.cpp ${PROJECT_SOURCE_DIR}/src/problem/*.cpp)

set (SOURCE_FILES ${CPP_FILES})

ADD_LIBRARY(ec SHARED ${SOURCE_FILES})

add_subdirectory(./examples/ackley)
add_subdirectory(./examples/griewangk)
add_subdirectory(./examples/rastrigin)
add_subdirectory(./examples/rosenbrock)
add_subdirectory(./examples/schwefel)
add_subdirectory(./examples/spherical)