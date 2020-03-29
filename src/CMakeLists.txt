project(smt-logger VERSION 1.0.0)

aux_source_directory(. DIR_SRCS)

if(UNIX)
  add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})
elseif(WIN32)
  add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
elseif(APPLE)
  add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})
endif()

# add pthread support
find_package(Threads)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# write version
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion)

# install headers
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/smt_logger.h)
install(FILES ${HEADER_FILES} DESTINATION include/${PROJECT_NAME})

# install everything
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# export xxxConfig.cmake, so that find_package() can find it
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE Leica::
        DESTINATION lib/cmake/${PROJECT_NAME})

configure_file(${PROJECT_NAME}Config.cmake.in ${PROJECT_NAME}Config.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})