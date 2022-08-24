//
// Created by sjhuang on 2022/8/23.
//

#ifndef WEB_SERVER_EVENT_HANDLE_H
#define WEB_SERVER_EVENT_HANDLE_H
#include <fcntl.h>
#include <sys/event.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>

class event_handle{
private:
    const int kReadEvent;
    const int kWriteEvent;
    const int kMaxEvents;
    const int bufferSize;
    int efd;
public:
    event_handle(const int buffer_size);
    ~event_handle();
    // 更新事件
    void update_events(int fd, int events, bool modify);
    // 处理 accept
    // TODO 增加一个 处理 accept 的回调函数
    void handleAccept(int lfd);
    void handleRead(int fd);
    void handleWrite(int fd);
    void handleError(int fd);

    // 处理一次可读/可写的
    void loop_once(int lfd, int waitms);

};


#endif //WEB_SERVER_EVENT_HANDLE_H
