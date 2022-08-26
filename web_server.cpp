//
// Created by sjhuang on 2022/8/20.
//

#include "web_server.h"


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

web_server::web_server(int port, int backlog, int buffer_size):server_port(port),backlog(backlog),buffer_size(buffer_size), server_ip_addr("127.0.0.1"){
    running = false;
    handle = new event_handle(buffer_size);
}

web_server::web_server():server_port(-1),backlog(5),buffer_size(4096), server_ip_addr("127.0.0.1"){
    running = false;
    handle = new event_handle(buffer_size);
}


void web_server::start(bool server) {
    running = true;
    if(server){
        return this->start_server();
    }
    return this->start_client();
}

void web_server::start_client() {
    // 创建 socket 套接字
    int sockfd = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0){
        throw std::exception();
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    init_serv_addr(&servaddr);
    if(connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        // todo connect error
        return;
    }
    printf("[client] 建立连接成功 port:%d\n",ntohs(servaddr.sin_port));
//    const char *msg = "client write 1-2-3-4-5";
//    size_t l = sizeof(msg);
//    int n = write(sockfd, msg, l);
//    if(n < 0){
//        std::cout << "write error" << std::endl;
//        throw std::exception();
//    }
    set_non_block(sockfd);
    handle->add_rw_events(sockfd);
    // todo 进行处理
    while(running){
        handle->loop_once(sockfd, 1000);
    }

}


void web_server::init(int port) {

}

web_server::~web_server(){

};

void web_server::start_server() {
    int listenfd, coonfd;
    // 创建 socket 套接字
    listenfd = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(listenfd < 0){
        throw std::exception();
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    init_serv_addr(&servaddr);
    // 监听，绑定端口port
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        throw std::exception();
    }
    // listen, closed -> listen 状态
    if(listen(listenfd,backlog) < 0){
        throw std::exception();
    }
    set_non_block(listenfd);
    handle->add_rw_events(listenfd);
    printf(" start a server at %s:%d, sockfd:%d \n", server_ip_addr, server_port, listenfd);
    // todo 进行处理
    while(running){
        handle->loop_once(listenfd, 1000);
    }

}