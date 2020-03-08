project(smt-logger VERSION 1.0.0)

# scan all cpp into DIR_SRCS var
aux_source_directory(. DIR_SRCS)

if(UNIX)
  add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})
elseif(WIN32)
  add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
elseif(APPLE)
  add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})
endif()

# add pthread src
find_package(Threads)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(FILES ../include/smt_logger.h DESTINATION include)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

install(EXPORT ${PROJECT_NAME}-targets
        NAMESPACE Leica::
        FILE ${PROJECT_NAME}-config.cmake
        DESTINATION lib/cmake/${PROJECT_NAME})
