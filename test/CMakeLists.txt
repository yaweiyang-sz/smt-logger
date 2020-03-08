project(test)

aux_source_directory(. DIR_SRCS)
add_executable(test ${DIR_SRCS})

TARGET_LINK_LIBRARIES(test
        ${CMAKE_PROJECT_NAME}
        ${CMAKE_THREAD_LIBS_INIT})