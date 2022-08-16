cmake_minimum_required(VERSION 3.19)
project(web_server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LOCK_QUEUE ./lock_queue/lock_block_queue.h ./lock_queue/lock_queue.h)
# 查找指定目录下的所有.cpp与.h文件 并存放到指定变量名SC_FILES中
FILE(GLOB SC_FILES "*.cpp" "*.h")

add_executable(web_server ${SC_FILES} ${LOCK_QUEUE})