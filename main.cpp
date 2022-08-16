#include <iostream>
#include "lock_queue/lock_block_queue.h"
//#include "lock_queue/lock_queue.h"

struct Task{
    int val;
    Task(int v):val(v){};
};
int main() {

    lock_queue<int> *q = new lock_block_queue<int>(10);
    for(int i = 0; i < 100; i++){
//        Task *task = new Task(i);
        if(q->push(i)){
            std::cout << i << "写入成功 ～"  << std::endl;
        }else{
            std::cout << i << "写入失败 ～"  << std::endl;
        }
    }

    while(!q->empty()){
        int task = 0;
        if(q->get(task)){
            std::cout << task << "读取成功 ～"  << std::endl;
        }

    }

    return 0;
}
