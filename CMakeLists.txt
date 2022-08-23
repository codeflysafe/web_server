cmake_minimum_required(VERSION 3.19)
project(web_server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(block_queue block_queue/lock_block_queue.h block_queue/block_queue.h)
set(thread_pool thread_pool/threadpool.h lock/lock.h)
set(http http/httpd.cpp http/httpd.h web_server.cpp web_server.h event/event_handle.cpp event/event_handle.h)
# 查找指定目录下的所有.cpp与.h文件 并存放到指定变量名SC_FILES中
FILE(GLOB SC_FILES "*.cpp" "*.h")
# 使用Threads包
#FIND_PACKAGE(Threads)
add_executable(web_server ${SC_FILES} ${LOCK_QUEUE} ${thread_pool} ${http})
#TARGET_LINK_LIBRARIES(web_server ${CMAKE_THREAD_LIBS_INIT})  # 链接${CMAKE_THREAD_LIBS_INIT}