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


template <typename T> lock_block_queue<T>::lock_block_queue(int cap):lock_queue<T>(cap) {
    if(pthread_rwlock_init(&this->rwlock,NULL) != 0){
        throw std::exception();
    }
}

template <typename T> lock_block_queue<T>::~lock_block_queue<T>() {
    // todo 析构函数
}

template <typename T> bool lock_block_queue<T>::try_push(const T &task) {
    // 获取锁成功
    if(pthread_rwlock_trywrlock(&this->rwlock) == 0){
        if(this->idx >= this->cap){
            // 此时已经满了，返回失败
            pthread_rwlock_unlock(&this->rwlock);
            return false;
        }else{
            // 如果没有满，则增加，返回成功
            this->idx += 1;
            this->tasks.push(task);
            pthread_rwlock_unlock(&this->rwlock);
            return true;
        }
    }
    return false;
}

// 从队列中弹出一个任务，失败返回false，成功则返回 true
template <typename T> bool lock_block_queue<T>::try_get(T &task) {
    if(pthread_rwlock_trywrlock(&this->rwlock) == 0){
        if(this->idx > 0){
            this->idx -= 1;
            // 避免复制，减少内存占用和copy
            task = std::move(this->tasks.front());
            pthread_rwlock_unlock(&this->rwlock);
            return true;
        }
        pthread_rwlock_unlock(&this->rwlock);
        return false;
    }
    return false;
}


template <typename T> bool lock_block_queue<T>::push(const T &task){
    // 获取锁成功
    pthread_rwlock_wrlock(&this->rwlock);
    if(this->idx >= this->cap){
        // 此时已经满了，返回失败
        pthread_rwlock_unlock(&this->rwlock);
        return false;
    }else{
        // 如果没有满，则增加，返回成功
        this->idx += 1;
        this->tasks.push(task);
        pthread_rwlock_unlock(&this->rwlock);
        return true;
    }
}

template <typename T> bool lock_block_queue<T>::get(T &task){
    pthread_rwlock_wrlock(&this->rwlock);
    if(this->idx > 0){
        this->idx -= 1;
        // 避免复制，减少内存占用和copy
        task = std::move(this->tasks.front());
        pthread_rwlock_unlock(&this->rwlock);
        return true;
    }
    pthread_rwlock_unlock(&this->rwlock);
    return false;
}


#endif //WEB_SERVER_LOCK_BLOCK_QUEUE_H
