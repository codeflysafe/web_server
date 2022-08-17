#include <iostream>
#include "lock_queue/lock_block_queue.h"
//#include "lock_queue/lock_queue.h"

struct Task{
    int val;
    Task(int v):val(v){};
};
int main() {

    lock_queue<Task *> *q = new lock_block_queue<Task *>(10);
    for(int i = 0; i < 100; i++){
        // 右值引用
        Task *task = new Task(i);
        if(q->push(task)){
            std::cout << i << "写入成功 ～"  << std::endl;
        }else{
            std::cout << i << "写入失败 ～"  << std::endl;
        }
    }

    while(!q->empty()){
        Task *task = new Task(1);
        if(q->get(std::move(task))){
            std::cout << task->val << "读取成功 ～"  << std::endl;
        }

    }

    return 0;
}
