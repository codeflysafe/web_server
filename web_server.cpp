//
// Created by sjhuang on 2022/8/20.
//

#include "web_server.h"

void web_server::start(bool server) {
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
    // connect success
}

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

    // epoll 进行i/o复用


}