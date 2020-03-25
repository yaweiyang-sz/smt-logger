project(tests)

aux_source_directory(. DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        ${CMAKE_PROJECT_NAME}
        ${CMAKE_THREAD_LIBS_INIT})