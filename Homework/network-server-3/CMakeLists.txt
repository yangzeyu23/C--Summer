cmake_minimum_required(VERSION 3.10)
project(network_server)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件
add_library(common STATIC src/common.cpp)
add_library(module STATIC src/module.cpp)
add_library(server STATIC src/server.cpp)

# 添加模块
add_library(diskfree SHARED src/modules/diskfree.cpp)
add_library(issue SHARED src/modules/issue.cpp)
add_library(process SHARED src/modules/process.cpp)
add_library(time SHARED src/modules/time.cpp)

# 主程序
add_executable(server_main src/main.cpp src/modules/time.cpp src/modules/issue.cpp src/modules/diskfree.cpp src/modules/process.cpp)
target_link_libraries(server_main common module server)