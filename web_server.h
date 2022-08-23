//
// Created by sjhuang on 2022/8/20.
//

#ifndef WEB_SERVER_WEB_SERVER_H
#define WEB_SERVER_WEB_SERVER_H
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include "event/event_handle.h"

class web_server {
public:
    web_server(int port, int backlog);
    ~web_server();
    void init(int port);
    // 开启一个服务, server true: 服务端， false client
    void start(bool server);


private:
    // 服务器端口
    const int server_port;
    const char * server_ip_addr;
    // 队列大小
    const int backlog;
    bool running;
    event_handle* handle;
    void start_server();
    void start_client();
    void init_serv_addr(struct sockaddr_in *serv_addr){
        serv_addr->sin_family = AF_INET;
        serv_addr->sin_port = htons(server_port);
        serv_addr->sin_addr.s_addr = inet_addr(server_ip_addr);
    }

};


#endif //WEB_SERVER_WEB_SERVER_H
