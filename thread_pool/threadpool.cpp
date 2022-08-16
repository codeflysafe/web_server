//
// Created by sjhuang on 2022/8/15.
//

#include "threadpool.h"

// https://mp.weixin.qq.com/s/PB8vMwi8sB4Jw3WzAKpWOQ

template<typename T> threadpool<T>::threadpool(int thread_num, int max_task_num) {
    this->max_thread_num = thread_num;
    this->cur_active_thread_num = 0;
    this->queue = lock_queue<T>(max_task_num);
    m_threds = new pthread_t[this->max_thread_num];
    if(!m_threds){
        throw std::exception();
    }
    for(int i = 0; i < this->m_threds; i++){
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

template<typename T> bool threadpool<T>::submit(T *task) {
    return this->queue.push(task);
}

/*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
template<typename T> static void *threadpool<T>::worker(void *arg) {
    threadpool  *pool = (threadpool *)(arg);
    pool->run();
}

template<typename T> void threadpool<T>::run() {
    // 如果正在运行中，从阻塞队列里面获取任务
    while(this->m_stop){
        T *task;
        // 如果存在任务，则执行
        if(this->queue.get(task)){
            // todo 如何处理请求
            std::cout << "接收到了一个新的任务 ， 我要做他 ～～～～～～" << endl;
        }
    }
}