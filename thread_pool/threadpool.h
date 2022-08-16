//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_THREADPOOL_H
#define WEB_SERVER_THREADPOOL_H
#include <iostream>
#include <pthread.h>

using  namespace  std;

template<typename T>
class threadpool {

public:
    threadpool(int thread_num = 8, int max_task_num = 1000);
    ~threadpool();
    // 向任务队列里面提交任务，当达到最大任务数量的时候，可能会block
    bool append(T *task);

private:
    // 开始执行
    void run();


private:

    // 当前活跃的线程队列
    pthread_t *m_threds;
    // 当前正在活跃的线程数量
    int cur_active_thread_num;
    // 线程池内活跃的最大线程数量
    int max_thread_num;



};


#endif //WEB_SERVER_THREADPOOL_H
