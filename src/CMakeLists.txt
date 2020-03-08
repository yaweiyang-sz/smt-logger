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

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/include/smt_logger.h)

# 写入库的版本信息
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion)

# 将库文件，可执行文件，头文件安装到指定目录
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

# 将库的相关信息输出为MyMathConfig.cmake，供find_package查找
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE Leica::
        DESTINATION lib/cmake/${PROJECT_NAME})

configure_file(${PROJECT_NAME}Config.cmake.in ${PROJECT_NAME}Config.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})