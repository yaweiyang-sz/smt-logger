project(smt_logger)

# add headers
include_directories(.)
include_directories(./spdlog/details)
include_directories(./spdlog/fmt)
include_directories(./spdlog/sinks)

# scan all cpp into DIR_SRCS var
aux_source_directory(. DIR_SRCS)

# set as static library
add_library(smt_logger STATIC ${DIR_SRCS})

# add pthread library
find_package (Threads)
target_link_libraries(smt_logger ${CMAKE_THREAD_LIBS_INIT})

######### install config begin ########
# set install dir for windows
if(WIN32)
	set(CMAKE_INSTALL_PREFIX D:\\CMAKE_ROOT)
endif()

# setup output
install(TARGETS smt_logger
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# setup headers
install(FILES ${PROJECT_SOURCE_DIR}/smt_logger.h DESTINATION include)
######## install config end ########
