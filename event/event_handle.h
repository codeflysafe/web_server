//
// Created by sjhuang on 2022/8/23.
//

#ifndef WEB_SERVER_EVENT_HANDLE_H
#define WEB_SERVER_EVENT_HANDLE_H
#include <fcntl.h>
#include <sys/event.h>

class event_handle{
private:
    const int kReadEvent;
    const int kWriteEvent;
public:
    event_handle();
    ~event_handle();
    // 更新事件
    void update_events(int efd, int fd, int events, bool modify);
    // 处理 accept
    // TODO 增加一个 处理 accept 的回调函数
    void handleAccept(int efd, int lfd);
    void handleRead(int efd, int fd);
    void handleWrite(int efd, int fd);
    void handleError(int efd, int fd);

    // 处理一次可读/可写的
    void loop_once(int efd, int lfd, int waitms);

};

// 非阻塞模式
int set_non_block(int fd){
    int flags;

    /* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
}

#endif //WEB_SERVER_EVENT_HANDLE_H
