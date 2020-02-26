project(tests)

include_directories(../library)

aux_source_directory(. DIR_SRCS)
add_executable(tests ${DIR_SRCS})

TARGET_LINK_LIBRARIES(tests ${CMAKE_PROJECT_NAME})
TARGET_LINK_LIBRARIES(tests ${CMAKE_THREAD_LIBS_INIT})