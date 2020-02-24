project(smt_logger)

# add headers
include_directories(.)
include_directories(./spdlog/details)
include_directories(./spdlog/fmt)
include_directories(./spdlog/sinks)

# scan all cpp into DIR_SRCS var
aux_source_directory(. DIR_SRCS)

# set as static library

if(UNIX)
  add_library(${CMAKE_PROJECT_NAME} SHARED ${DIR_SRCS})
elseif(WIN32)
  add_library(${CMAKE_PROJECT_NAME} STATIC ${DIR_SRCS})
elseif(APPLE)
  add_library(${CMAKE_PROJECT_NAME} SHARED ${DIR_SRCS})
endif()

# add pthread library
find_package(Threads)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# install script
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS ${CMAKE_PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(EXPORT ${CMAKE_PROJECT_NAME}-targets
        FILE ${CMAKE_PROJECT_NAME}-targets.cmake
        NAMESPACE Leica::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME})

install(FILES ${PROJECT_SOURCE_DIR}/smt_logger.h DESTINATION include)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/${CMAKE_PROJECT_NAME}-config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME})