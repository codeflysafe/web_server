//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_LOCK_BLOCK_QUEUE_H
#define WEB_SERVER_LOCK_BLOCK_QUEUE_H
#include <semaphore>
#include <queue>
#include <atomic>
#include <pthread.h>
#include "block_queue.h"

template<typename T>
class lock_block_queue : public block_queue<T>{
public:
    lock_block_queue(const int cap);
    virtual ~lock_block_queue();
    // 放入任务, 这里使用右值引用
    virtual bool push(const T &task);
    // 取出任务
    virtual bool take(T &task);

private:
    mutable pthread_mutex_t lock;
    mutable pthread_cond_t cond;
};


template <typename T> lock_block_queue<T>::lock_block_queue(const int cap):block_queue<T>(cap) {

    if(pthread_mutex_init(&this->lock,NULL) != 0){
        throw std::exception();
    }

    if(pthread_cond_init(&this->cond, NULL) != 0){
        throw std::exception();
    }
}

template <typename T> lock_block_queue<T>::~lock_block_queue<T>() {
    // todo 析构函数
}

template <typename T> bool lock_block_queue<T>::push(const T &task){
    // 获取锁成功
    pthread_mutex_lock(&this->lock);
    if(this->idx >= this->cap){
        // 此时已经满了，唤醒一个线程处理
        pthread_cond_signal(&this->cond);
        pthread_mutex_unlock(&this->lock);
        return false;
    }
    // 如果没有满，则增加，返回成功
    this->idx += 1;
    this->tasks.emplace(task);
    pthread_cond_signal(&this->cond);
    pthread_mutex_unlock(&this->lock);
    return true;
}

template <typename T> bool lock_block_queue<T>::take(T &task){
    pthread_mutex_lock(&this->lock);
    // 如果没有任务，则阻塞
    while(this->idx <= 0){
        if(0 != pthread_cond_wait(&cond, &lock)){
            pthread_mutex_unlock(&lock);
            return false;
        }
    }
    this->idx -= 1;
    // 避免复制，减少内存占用和copy
    task = std::move(this->tasks.front());
    this->tasks.pop();
    pthread_mutex_unlock(&this->lock);
    return true;
}


#endif //WEB_SERVER_LOCK_BLOCK_QUEUE_H
