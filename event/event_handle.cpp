//
// Created by sjhuang on 2022/8/23.
//

#include "event_handle.h"
event_handle::event_handle():kWriteEvent(2), kReadEvent(1), kMaxEvents(20){
    efd = kqueue();
    if(efd < 0){
        throw std::exception();
    }
}
event_handle::~event_handle() {
}

void event_handle::handleAccept(int lfd) {
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    int cfd = accept(lfd, (struct sockaddr *)&addr, &socklen);
    if(cfd < 0){
        throw std::exception();
    }

    // todo 做一些业务处理

    set_non_block(cfd);
    // 去监听 cfd 的可读/可写等等事件
    update_events(cfd, kReadEvent|kWriteEvent, false);
}

void event_handle::handleWrite(int fd) {
    // todo
}


void event_handle::handleRead(int fd) {
    //todo 处理读，要一次读完，

}

void event_handle::handleError(int fd) {
    // todo 处理错误
}

void event_handle::loop_once(int lfd, int waitms) {
    struct timespec timeout;
    timeout.tv_sec = waitms/1000;
    timeout.tv_nsec = (waitms % 1000)*1000 * 1000;
    struct kevent active_kevents[kMaxEvents];
    int n = kevent(efd, active_kevents, kMaxEvents, nullptr, 0, &timeout);
    for(int i = 0; i < n; i++){
        int fd = (int)(intptr_t)(active_kevents[i].udata);
        int events = active_kevents[i].filter;
        // 可读操作
        if(events == EVFILT_READ){
            // accept 准备就绪，这里
            if(fd == lfd){
                handleAccept( lfd);
            }else{
                handleRead( fd);
            }
        }else if(events == EVFILT_WRITE){
            handleWrite( fd);
        }else{
            handleError( fd);
//            throw std::exception();
        }
    }
}