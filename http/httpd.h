//
// Created by sjhuang on 2022/8/20.
//

#ifndef WEB_SERVER_HTTPD_H
#define WEB_SERVER_HTTPD_H
#include <iostream>
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unordered_map>
#include <string>
#include <errno.h>
#include "../util/strings.h"
#define READ_BUFFER_SIZE 2048

using namespace std;

enum METHOD{
    GET = 0,
    POST,
};

enum HTTP_CODE{
    NO_REQUEST,
    GET_REQUEST,
    BAD_REQUEST,
    NO_RESOURCE,
    FORBIDDEN_REQUEST,
    FILE_REQUEST,
    INTERNAL_ERROR,
    CLOSED_CONNECTION
};

enum LINE_STATUS
{
    LINE_OK = 0,
    LINE_BAD,
    LINE_OPEN
};

enum PARSE_STATUS{
    PARSE_METHOD = 0,
    PARSE_HEADER,
    PARSE_CONTEXT,
    PARSE_ERROR,
};


class httpd {
public:
    httpd();
    ~httpd();
    void init(int sockfd, const sockaddr_in &addr);
    void close_coon();
    void parse();
    bool read_once();
    LINE_STATUS parse_line();
    HTTP_CODE parse_request_line(char *text);
    HTTP_CODE parse_header_line(char *text);
    HTTP_CODE parse_content(char *text);

private:
    char *get_line();

private:
    // socket fd
    int sockfd;
    sockaddr_in addr;
    char buffer[READ_BUFFER_SIZE];
    int cur_buffer_idx;
    int m_start_line;
    int m_checked_idx;
    string m_url;
    string m_version;
    string m_string;
    METHOD m_method;
    unordered_map<string, string> head_params;
    LINE_STATUS line_status;
    PARSE_STATUS parse_status;
    HTTP_CODE http_code;
};


#endif //WEB_SERVER_HTTPD_H
