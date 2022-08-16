//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_LOCK_QUEUE_H
#define WEB_SERVER_LOCK_QUEUE_H
#include <queue>

template <typename T>
class lock_queue{
public:
    lock_queue(int cap);
    virtual ~lock_queue();
    // 纯虚函数
    virtual bool push(const T &task) = 0;
    // 纯虚函数
    virtual bool get(T &task) = 0;
    // 纯虚函数
    virtual bool try_push(const T &task) = 0;
    // 纯虚函数
    virtual bool try_get(T &task) = 0;
    bool empty();
    int size();


private:
    int cap;
    volatile int idx;
    // 任务队列
    std::queue<T *> tasks;
};

template<typename T> bool lock_queue<T>::empty() {
    return idx == 0;
}

template<typename T> int lock_queue<T>::size() {
    return idx;
}

template<typename T> lock_queue<T>::lock_queue(int cap) {
    this->idx = 0;
    this->cap = cap;
}

#endif //WEB_SERVER_LOCK_QUEUE_H
