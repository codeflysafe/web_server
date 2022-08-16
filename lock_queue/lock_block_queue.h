//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_LOCK_BLOCK_QUEUE_H
#define WEB_SERVER_LOCK_BLOCK_QUEUE_H
#include <semaphore>
#include <queue>
#include <atomic>
#include <pthread.h>
#include "lock_queue.h"
template<typename T>
class lock_block_queue : public lock_queue<T>{
public:
    lock_block_queue(int cap);
    virtual ~lock_block_queue();
    // 放入任务, 这里使用右值引用
    virtual bool try_push(const T &task);
    // 取出任务
    virtual bool try_get(T &task);
    // 放入任务, 这里使用右值引用
    virtual bool push(const T &task);
    // 取出任务
    virtual bool get(T &task);

private:
    mutable pthread_rwlock_t rwlock;
    mutable pthread_cond_t cond;
};


#endif //WEB_SERVER_LOCK_BLOCK_QUEUE_H
