cmake_minimum_required(VERSION 3.0.0)
project(smt_logger)

# change output dirs
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_DEBUG_POSTFIX d)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DLOG_DEBUG)
endif ()

add_subdirectory(src)
add_subdirectory(testcase)