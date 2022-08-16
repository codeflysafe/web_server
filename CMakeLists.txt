cmake_minimum_required(VERSION 3.19)
project(web_server)

set(CMAKE_CXX_STANDARD 11)

add_executable(web_server main.cpp thread_pool/threadpool.cpp thread_pool/threadpool.h lock_queue/lock_block_queue.cpp lock_queue/lock_block_queue.h lock_queue/lock_queue.h)