//
// Created by sjhuang on 2022/8/23.
//

#include "event_handle.h"
event_handle::event_handle(const int buffer_size):kWriteEvent(2), kReadEvent(1), kMaxEvents(20),bufferSize(buffer_size){
    efd = kqueue();
    if(efd < 0){
        throw std::exception();
    }
}
event_handle::~event_handle() {

}

// 更新事件监听
void event_handle::update_events(int fd, int events, bool modify) {

    struct kevent ev[2];
    int n = 0;
    if (events & kReadEvent) {
        EV_SET(&ev[n++], fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, (void *) (intptr_t) fd);
    } else if (modify) {
        EV_SET(&ev[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, (void *) (intptr_t) fd);
    }
    if (events & kWriteEvent) {
        EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, (void *) (intptr_t) fd);
    } else if (modify) {
        EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, (void *) (intptr_t) fd);
    }
//    printf("%s fd %d events read %d write %d\n",
//           modify ? "mod" : "add", fd, events & kReadEvent, events & kWriteEvent);
    // 注册的方法是通过 kevent() 将 eventlist 和 neventlist 置成 NULL 和 0 来达到的。
    int r = kevent(efd, ev, n, nullptr, 0, nullptr);
    if(r > 0) throw std::exception();

}

void event_handle::handleAccept(int lfd) {

    struct sockaddr_in cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    int cfd = accept(lfd, (struct sockaddr *)&cli_addr, &socklen);
    if(cfd < 0){
        throw std::exception();
    }
    char buff[30];
    printf("[Server] connection from %s port: %d\n", inet_ntop(AF_INET, &cli_addr.sin_addr, buff, sizeof(buff)),ntohs(cli_addr.sin_port));
    // todo 做一些业务处理

    // 去监听 cfd 的可读/可写等等事件
    add_rw_events(cfd);
}

void event_handle::handleWrite(int fd) {
    // todo 处理写事件
    char msg[bufferSize];
    sprintf(msg," wojieshoudaole xxxxxxx fd:%d",fd);
    write(fd, msg, sizeof(msg));
//    close(fd);
}


void event_handle::handleRead(int fd) {
    //todo 处理读，要一次读完，
    char buffer[bufferSize];
    int n = 0;
    printf("recv data are: \n");
    memset(buffer,0, bufferSize);
    while((n = read(fd, buffer, bufferSize - 1)) > 0){
        // todo 读出来的数据，如何处理呢？
        printf("%s \n", buffer);
    }
    if(n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        return;
    }
    if(n < 0){
        printf("error :%d \n", errno);
//        close(fd);
//        throw std::exception();
    }

}

void event_handle::handleError(int fd) {
    // todo 处理错误
    // 关闭 fd
    printf(" error fd: %d\n", fd);
//    close(fd);
}

void event_handle::add_rw_events(int fd){
    update_events(fd, kWriteEvent|kReadEvent, false);
}

void event_handle::loop_once(int lfd, int waitms) {
    struct timespec timeout;
    if(waitms >= 0){
        timeout.tv_sec = waitms/1000;
        timeout.tv_nsec = (waitms % 1000)*1000 * 1000;
    }
    struct kevent active_kevents[kMaxEvents];
    int n = kevent(efd, nullptr, 0, active_kevents, kMaxEvents, waitms < 0? nullptr:&timeout);
    if(n < 0){
        throw std::exception();
    }
    for(int i = 0; i < n; i++){
        int fd = (int)(intptr_t)(active_kevents[i].udata);
        int events = active_kevents[i].filter;
//        printf("lfd: %d fd:%d and events:%d :\n",lfd, fd, events);
        // 可读操作
        if(events == EVFILT_READ){
            // accept 准备就绪，这里
            if(fd == lfd){
                handleAccept(lfd);
            }else{
                handleRead(fd);
            }
        }else if(events == EVFILT_WRITE){
            handleWrite( fd);
        }else{
            printf("error : %d \n", errno);
            handleError( fd);
//            throw std::exception();
        }
    }
}