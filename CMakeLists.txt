cmake_minimum_required(VERSION 3.0.0)

project(smt-logger)
set(smt-logger_VERSION 1.0.0)

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

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY VERSION ${smt-logger_VERSION})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY SOVERSION 1)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY INTERFACE_smt-logger_MAJOR_VERSION 0)
set_property(TARGET ${CMAKE_PROJECT_NAME} APPEND PROPERTY
        COMPATIBLE_INTERFACE_STRING smt-logger_MAJOR_VERSION)

# install script
SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(FILES ${PROJECT_SOURCE_DIR}/library/smt_logger.h DESTINATION include)

install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${CMAKE_PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${smt-logger_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(EXPORT ${CMAKE_PROJECT_NAME}Targets
        FILE ${CMAKE_PROJECT_NAME}Targets.cmake
        NAMESPACE Leica::
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

install(FILES cmake/${CMAKE_PROJECT_NAME}Config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME}})