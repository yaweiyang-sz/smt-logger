cmake_minimum_required(VERSION 3.0.0)

project(smt-logger)

# change output dirs
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DLOG_DEBUG)
endif ()

add_subdirectory(library)
add_subdirectory(tests)

# install script
SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(FILES ${PROJECT_SOURCE_DIR}/library/smt_logger.h DESTINATION include)

install(TARGETS ${CMAKE_PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}-targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(EXPORT ${CMAKE_PROJECT_NAME}-targets
        NAMESPACE Leica::
        FILE ${CMAKE_PROJECT_NAME}-config.cmake
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})