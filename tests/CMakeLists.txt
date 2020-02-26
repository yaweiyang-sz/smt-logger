project(testcase)

include_directories(../library)

aux_source_directory(. DIR_SRCS)
add_executable(testcase ${DIR_SRCS})

TARGET_LINK_LIBRARIES(testcase ${CMAKE_PROJECT_NAME})
TARGET_LINK_LIBRARIES(testcase ${CMAKE_THREAD_LIBS_INIT})