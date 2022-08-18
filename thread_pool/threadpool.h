//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_THREADPOOL_H
#define WEB_SERVER_THREADPOOL_H
#include <iostream>
#include <pthread.h>
#include "../block_queue/block_queue.h"
#include "../block_queue/lock_block_queue.h"

using  namespace  std;

template<typename T>
class threadpool {

public:
    threadpool(bool block_queue = true,int thread_num = 8, int max_task_num = 1000);
    ~threadpool();
    // 向任务队列里面提交任务，当达到最大任务数量的时候，可能会block
    bool submit(const T& task);

private:
    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static void *worker(void *arg);
    // 开始执行
    void run();


private:
    // 当前活跃的线程队列
    pthread_t* m_threds;
    // 当前正在活跃的线程数量
    int cur_active_thread_num;
    // 线程池内活跃的最大线程数量
    int max_thread_num;
    // 是否停止允许
    volatile bool m_stop;
    // 任务队列
    block_queue<T> *queue;

};


template<typename T> threadpool<T>::threadpool(bool block_queue , int thread_num, int max_task_num) {
    this->max_thread_num = thread_num;
    this->cur_active_thread_num = 0;
    this->m_stop = true;
    if(block_queue){
        this->queue = new lock_block_queue<T>(max_task_num);
    }
    m_threds = new pthread_t[this->max_thread_num];
    if(!m_threds){
        throw std::exception();
    }
    for(int i = 0; i < this->max_thread_num; i++){
        if( pthread_create(m_threds+i, NULL, worker, this) != 0){
            delete [] m_threds;
            throw std::exception();
        }

        //将线程进行分离后，不用单独对工作线程进行回收
        if(pthread_detach(m_threds[i])){
            delete []m_threds;
            throw std::exception();
        }
        this->cur_active_thread_num = thread_num;
    }
}

template<typename T> threadpool<T>::~threadpool() {
    //todo 释放内存
}

template<typename T> bool threadpool<T>::submit(const T& task) {
    return this->queue->push(task);
}

/*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
template<typename T> static void *threadpool<T>::worker(void *arg) {
    threadpool  *pool = (threadpool *)(arg);
    pool->run();
}

template<typename T> void threadpool<T>::run() {
    // 如果正在运行中，从阻塞队列里面获取任务
    while(this->m_stop){
        T task {};
        // 如果存在任务，则执行
        if(this->queue->take(task)){
            // todo 如何处理请求
            std::cout << "接收到了一个新的任务 ， 我要做他 ～～～～～～" << &task << endl;

        }
    }
}


#endif //WEB_SERVER_THREADPOOL_H
