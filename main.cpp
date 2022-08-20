#include <iostream>
#include "thread_pool/threadpool.h"
//#include "block_queue/block_queue.h"
#include <chrono>
#include <thread>
struct Task{
    int val;
    Task():val(-1){};
    Task(int v):val(v){};
};
int main() {
    threadpool<Task> *pool = new threadpool<Task>();
    for(int i = 0; i < 100; i++){
        Task t = Task(i);
        pool->submit(t);
        if(i == 50){
            pool->stop();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    return 0;
}
