//
// Created by sjhuang on 2022/8/15.
//

#ifndef WEB_SERVER_BLOCK_QUEUE_H
#define WEB_SERVER_BLOCK_QUEUE_H
#include <queue>

template <typename T>
class block_queue{
public:
    block_queue(const int cap);
    block_queue(const block_queue &) = delete;
    block_queue &operator= (const block_queue &) = delete;
    virtual ~block_queue();
    // 纯虚函数
    //
    virtual bool push(const T& t) = 0;
    // 纯虚函数
    virtual bool take(T &t) = 0;

    bool empty();
    int size();


protected:
    int cap;
    volatile int idx;
    // 任务队列
    std::queue<T> tasks;
};

template<typename T> bool block_queue<T>::empty() {
    return idx == 0;
}

template<typename T> int block_queue<T>::size() {
    return idx;
}

template<typename T> block_queue<T>::block_queue(const int cap) {
    this->idx = 0;
    this->cap = cap;
}

template<typename T> block_queue<T>::~block_queue(){

}

#endif //WEB_SERVER_BLOCK_QUEUE_H
