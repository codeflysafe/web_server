//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_THREADPOOL_H
#define WEB_SERVER_THREADPOOL_H
#include <iostream>
#include <pthread.h>
#include "../lock_queue/lock_queue.h"

using  namespace  std;

template<typename T>
class threadpool {

public:
    threadpool(int thread_num = 8, int max_task_num = 1000);
    ~threadpool();
    // 向任务队列里面提交任务，当达到最大任务数量的时候，可能会block
    bool submit(T *task);

private:
    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static void *worker(void *arg);
    // 开始执行
    void run();


private:

    // 当前活跃的线程队列
    pthread_t *m_threds;
    // 当前正在活跃的线程数量
    int cur_active_thread_num;
    // 线程池内活跃的最大线程数量
    int max_thread_num;
    // 是否停止允许
    volatile bool m_stop;
    // 任务队列
    lock_queue<T> queue;

};


#endif //WEB_SERVER_THREADPOOL_H
