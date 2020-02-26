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